#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/ml/ml.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include"opencv2/imgproc/imgproc.hpp"
#include<stdio.h>
#include<opencv2/opencv.hpp>
#include<iostream>


using namespace cv;
using namespace std;



class Camera{
private:
	VideoCapture cap;
	Mat frame;
	
public:
	Camera();
	void capture();
	void showCam();
	Mat getFrame();
};

