#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/ml/ml.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <cmath>
#include "math.h"
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <iostream>
#include "JHPWMPCA9685.h"
#include<iostream>
#include<sstream>

#include "Camera.cpp"


using namespace cv;
using namespace std;




class LaneDetr{
private:
	Camera camera;
	Mat frame;
	Mat ROI;
	double devn;
	double deg, rad;
	vector<Vec4i> lines;
	int x, y, width, height;
	Vec4i L_tmp;
public:
	LaneDetr();
	void detectLanes();
	void drawLanes();
	void showLanes();
	double getDeg();
	double getDevn();
	bool isYellowlane();
	bool isStopline();
	void setRange(int x, int y, int widht, int height);
};




