#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    // 동영상 파일 열기
    VideoCapture video("input.mp4");

    if (!video.isOpened()) {
        cout << "동영상 파일을 열 수 없습니다." << endl;
        return -1;
    }

    // 동영상 파일의 속성 가져오기
    double fps = video.get(CAP_PROP_FPS);
    int width = video.get(CAP_PROP_FRAME_WIDTH);
    int height = video.get(CAP_PROP_FRAME_HEIGHT);

    // 동영상 저장을 위한 비디오 라이터 생성
    VideoWriter writer("output_video.mp4", VideoWriter::fourcc('X', 'V', 'I', 'D'), fps, Size(width, height), false);

    if (!writer.isOpened()) {
        cout << "동영상 파일을 저장할 수 없습니다." << endl;
        return -1;
    }

    Mat img_frame;
    Mat grayscaleFrame;
    Mat output;
    UMat img_hsv, img_combine;
    UMat white_mask, white_image;
    UMat yellow_mask, yellow_image;


    while (1) {

        if(!video.read(img_frame)) break;
        img_frame.copyTo(output);


        //차선검출
        Scalar lower_white = Scalar(200, 200, 200); //흰색 차선 RGB
        Scalar upper_white = Scalar(255, 255, 255); 
        Scalar lower_yellow = Scalar(10, 100, 100); //노란색 차선 HSV
        Scalar upper_yellow = Scalar(40, 255, 255);

        inRange(output, lower_white, upper_white, white_mask);
        bitwise_and(output, output, white_image, white_mask); //흰색 필터링

        cvtColor(output, img_hsv, COLOR_BGR2HSV);

        inRange(img_hsv, lower_yellow, upper_yellow, yellow_mask);
        bitwise_and(output, output, yellow_image, yellow_mask); //노란색 필터링

        addWeighted(white_image, 1.0, yellow_image, 1.0, 0.0, output);

        // 프레임을 GrayScale로 변환
        cvtColor(output, grayscaleFrame, COLOR_BGR2GRAY);

        // 변환된 프레임을 출력 동영상에 저장
        writer.write(grayscaleFrame);

        // 변환된 프레임을 화면에 출력
        imshow("Grayscale Video", grayscaleFrame);

        // ESC 키를 누르면 종료
        if (waitKey(1) == 27)
            break;
        //수정사항발생123//
    }

    // 리소스 해제
    video.release();
    writer.release();
    destroyAllWindows();

    return 0;
}