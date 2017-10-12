#include "ImgMatcher.h"




ImgMatcher::ImgMatcher(Mat frame){
	imwrite("frame.jpg", frame);
	refImg = imread("frame.jpg", CV_LOAD_IMAGE_GRAYSCALE);
}



double ImgMatcher::getSimi(String trgImgName){
	trgImg = imread(trgImgName, CV_LOAD_IMAGE_GRAYSCALE);
	refImg.copyTo(resImg);

	int resCols = abs(refImg.cols - trgImg.cols) + 1;
	int resRows = abs(refImg.rows - trgImg.rows) + 1;

	cmpImg.create( resCols, resRows, CV_32FC1 );
	matchTemplate( refImg, trgImg, cmpImg, TM_CCOEFF_NORMED );
	//normalize( cmpImg, cmpImg, 0, 1, NORM_MINMAX, -1, Mat() );
	minMaxLoc( cmpImg, &min, &max, &minLoc, &maxLoc, Mat() );
	//rectangle( resImg, maxLoc, Point( maxLoc.x + trgImg.cols , maxLoc.y + trgImg.rows),Scalar::all(255), 2, 8, 0 );
	return max;
}

Mat ImgMatcher::drawRect(Mat frame){
	rectangle(frame, maxLoc, Point( maxLoc.x + trgImg.cols , maxLoc.y + trgImg.rows),Scalar::all(255), 2, 8, 0 );
	return frame;
}





