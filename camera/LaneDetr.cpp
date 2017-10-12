#include "LaneDetr.h"
#include "ImgMatcher.cpp"
#include <math.h>


LaneDetr::LaneDetr(){
}


bool LaneDetr::isYellowlane(){
	int num1 = (L_tmp[0] + L_tmp[2])/2;
	int num2 = (L_tmp[1] + L_tmp[3])/2;

	int num3 = num1-15;
	int num4 = num2 -6;

	num1 += 15;
	num2 += 6;
	cout << "num1: " << num1 << endl;
	cout << "num2: " << num2 << endl<<endl;

	Vec3b* pixel = frame.ptr<Vec3b>(num2);
	Vec3b* pixel1 = frame.ptr<Vec3b>(num4);



	int R = pixel[num1][2];
	int G = pixel[num1][1];
	int B = pixel[num1][0];
	
	int R1 = pixel[num3][2];
	int G1 = pixel[num3][1];
	int B1 = pixel[num3][0];

	if((R>200 && G>200 && B<100) || (R1>200 && G1>200 && B1<100)){
		return true;
	}
	return false;
}

bool LaneDetr::isStopline(){
	if((deg>=170 && deg<=180) || (deg<=10 && deg>=0)){
		return true;
	}
	return false;
}




void LaneDetr::detectLanes(){
	Mat Edge, Gray;
	
	camera.capture();
	frame = camera.getFrame();
	
	ROI = Mat(frame, Rect(x-10, y-10, width+20, height+10));

	cvtColor(ROI, Gray, CV_RGB2GRAY);
	Canny(Gray, Edge, 150,300,3);
	ROI = Mat(Edge, Rect(10, 10, width, height));
	HoughLinesP(ROI, lines, 1, CV_PI/180, 50, 50, 10);

	for(int j=0; j<lines.size(); j++){
		L_tmp = lines[0];

		L_tmp[0] += x; L_tmp[2] += x;
		L_tmp[1] += y; L_tmp[3] += y;
		

		rad = (L_tmp[1]-L_tmp[3])/(double)(L_tmp[0]-L_tmp[2]) * -1;
		deg = atan(rad) *  (180.0/3.14);

		if(deg<0) {deg += 180; if(deg>=130)devn=1; else devn=(deg-50)/(130-50);}
		else {if(deg<=25)devn=-1; else devn=(50-deg)/25 * -1;}
	}
}



void LaneDetr::drawLanes(){
	line(frame, Point(L_tmp[0], L_tmp[1]), Point(L_tmp[2], L_tmp[3]), Scalar(0,0,255),1);
	line(frame, Point(x, y), Point(x+width, y), Scalar(0,0,255),1);
	line(frame, Point(x, y), Point(x, y+height), Scalar(0,0,255),1);
	line(frame, Point(x+width, y), Point(x+width, y+height), Scalar(0,0,255),1);	
}


void LaneDetr::showLanes(){
	imshow("LaneDetr", frame);
}

void LaneDetr::setRange(int X, int Y, int Width, int Height){
	x = X;
	y = Y;
	width = Width;
	height = Height;
}



double LaneDetr::getDevn(){
	return devn;
}

double LaneDetr::getDeg(){
	return deg;
}




