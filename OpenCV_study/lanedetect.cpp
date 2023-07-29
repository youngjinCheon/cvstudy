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
    return output; 
}

Mat detect::region(Mat img_edge)
{
    int width = img_edge.cols;
    int height = img_edge.rows;

    Mat output;
    Mat mask = Mat::zeros(height, width, CV_8UC1);

    Point points[4]{
        Point((width * (1 - limit_bottom)) / 2, height),
         Point((width * (1 - limit_top)) / 2, height - height * limit_height),
          Point(width - (width * (1 - limit_top)) / 2, height - height * limit_height),
           Point(width - (width * (1 - limit_bottom)) / 2, height)
    };

    fillConvexPoly(mask, points, 4, Scalar(255, 0, 0));
    bitwise_and(img_edge, mask, output);

    return output;
}

vector<Vec4i> detect::houghline(Mat img_region)
{
    vector<Vec4i> line;

    HoughLinesP(img_region, line, 1, CV_PI / 180, 20, 10, 20);
    return line;
}

vector<vector<Vec4i>> detect::seperateline(Mat img_edge, vector<Vec4i> lines)
{

}
