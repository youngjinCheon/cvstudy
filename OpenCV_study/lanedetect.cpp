#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include "detect.h"

Mat detect::colors(Mat img_frame)
{
    Mat output;
    UMat img_hsv, img_combine;
    UMat white_mask, white_image;
    UMat yellow_mask, yellow_image;

    img_frame.copyTo(output);

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
    return output; 


}