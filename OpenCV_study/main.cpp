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


    while (1) {

        if(!video.read(img_frame)) break;
     
        img_color = detection.colors(img_frame);

        // �������� GrayScale�� ��ȯ
        cvtColor(img_color, grayscaleFrame, COLOR_BGR2GRAY);

        //��������
        Canny(grayscaleFrame, img_edge, 50, 150);

        //���ɿ�������
        img_region = detection.region(img_edge);

        //hough���� ����
        lines = detection.houghline(img_region);

        // ��ȯ�� �������� ��� ������ ����
        writer.write(img_region);

        // ��ȯ�� �������� ȭ�鿡 ���
        imshow("Grayscale Video",img_region);

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