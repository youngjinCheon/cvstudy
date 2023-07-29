#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "opencv2/opencv.hpp"

#include "detect.h"

using namespace std;
using namespace cv;

int main()
{
    detect detection;
    Mat img_frame, img_color, img_edge, img_region;
    vector<Vec4i> lines;
    Mat grayscaleFrame;

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


    while (1) {

        if(!video.read(img_frame)) break;
     
        img_color = detection.colors(img_frame);

        // 프레임을 GrayScale로 변환
        cvtColor(img_color, grayscaleFrame, COLOR_BGR2GRAY);

        //엣지검출
        Canny(grayscaleFrame, img_edge, 50, 150);

        //관심영역지정
        img_region = detection.region(img_edge);

        //hough직선 검출
        lines = detection.houghline(img_region);

        // 변환된 프레임을 출력 동영상에 저장
        writer.write(img_region);

        // 변환된 프레임을 화면에 출력
        imshow("Grayscale Video",img_region);

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