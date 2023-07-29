#pragma once
#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

class detect
{
private:
	double limit_bottom = 0.85;
	double limit_top = 0.06;
	double limit_height = 0.4;


public:
	Mat colors(Mat img_frame);
	Mat region(Mat img_edge);
	vector<Vec4i> houghline(Mat img_region);
	vector<vector<Vec4i>> seperateline(Mat img_edge, vector<Vec4i> lines);


};
