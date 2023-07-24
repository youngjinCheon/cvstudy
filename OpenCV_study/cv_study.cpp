#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    // ������ ���� ����
    VideoCapture video("input.mp4");

    if (!video.isOpened()) {
        cout << "������ ������ �� �� �����ϴ�." << endl;
        return -1;
    }

    // ������ ������ �Ӽ� ��������
    double fps = video.get(CAP_PROP_FPS);
    int width = video.get(CAP_PROP_FRAME_WIDTH);
    int height = video.get(CAP_PROP_FRAME_HEIGHT);

    // ������ ������ ���� ���� ������ ����
    VideoWriter writer("output_video.mp4", VideoWriter::fourcc('X', 'V', 'I', 'D'), fps, Size(width, height), false);

    if (!writer.isOpened()) {
        cout << "������ ������ ������ �� �����ϴ�." << endl;
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


        //��������
        Scalar lower_white = Scalar(200, 200, 200); //��� ���� RGB
        Scalar upper_white = Scalar(255, 255, 255); 
        Scalar lower_yellow = Scalar(10, 100, 100); //����� ���� HSV
        Scalar upper_yellow = Scalar(40, 255, 255);

        inRange(output, lower_white, upper_white, white_mask);
        bitwise_and(output, output, white_image, white_mask); //��� ���͸�

        cvtColor(output, img_hsv, COLOR_BGR2HSV);

        inRange(img_hsv, lower_yellow, upper_yellow, yellow_mask);
        bitwise_and(output, output, yellow_image, yellow_mask); //����� ���͸�

        addWeighted(white_image, 1.0, yellow_image, 1.0, 0.0, output);

        // �������� GrayScale�� ��ȯ
        cvtColor(output, grayscaleFrame, COLOR_BGR2GRAY);

        // ��ȯ�� �������� ��� ������ ����
        writer.write(grayscaleFrame);

        // ��ȯ�� �������� ȭ�鿡 ���
        imshow("Grayscale Video", grayscaleFrame);

        // ESC Ű�� ������ ����
        if (waitKey(1) == 27)
            break;
        //�������׹߻�123//
    }

    // ���ҽ� ����
    video.release();
    writer.release();
    destroyAllWindows();

    return 0;
}