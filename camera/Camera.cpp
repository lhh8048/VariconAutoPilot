#include "Camera.h"
#include <time.h>





Camera::Camera(){
	cap = VideoCapture("nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)1280, height=(int)720,format=(string)I420, framerate=(fraction)24/1 ! nvvidconv flip-method=2 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink");

	if (!cap.isOpened()){
		cout << "Failed to open camera." << endl;
	}	
}




void Camera::capture(){
	cap >> frame;
}


void Camera::showCam(){
	for(;;){
		cap >> frame;
		imshow("Camera", frame );
		
		waitKey(1);
	}
}

Mat Camera::getFrame(){
	return frame;
}