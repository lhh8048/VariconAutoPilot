#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/ml/ml.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include<iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;



class ImgMatcher{

private:
	Mat refImg;
	Mat trgImg;
	Mat cmpImg;
	Mat resImg;
	Point minLoc, maxLoc;
	double min, max;

public:
	ImgMatcher(Mat frame);
	double getSimi(String trgImgName);
	Mat drawRect(Mat frame);
};

