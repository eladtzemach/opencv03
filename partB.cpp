#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>

using namespace cv;
using namespace std;

//load image
Mat frame1 = imread("C:/.../images/Picture3.png", CV_LOAD_IMAGE_UNCHANGED);
Mat frame2;
int hue = 2;
Scalar YG_lower = Scalar(36, 50, 50); //Yellow-Green lower bound
Scalar YG_upper = Scalar(36, 255, 255); //Yellow-Green upper bound
Scalar V_lower = Scalar(148, 50, 50); //Violet lower bound
Scalar V_upper = Scalar(148, 255, 255); //Violet upper bound
Scalar R_lower = Scalar(0, 140, 140); //Red lower bound
Scalar R_upper = Scalar(0, 255, 255); //Red upper bound

										//hue=0 -> Yellow-Green
										//hue=1 -> Violet
										//hue=2 -> Red
										
//the function that is called when the tracker is moved
void callFunc(int, void*) {

	Mat frame3, frame4, mask;
	cvtColor(frame1, frame3, CV_BGR2HSV);


	if (hue == 0) {
		inRange(frame3, YG_lower, YG_upper, mask);
		frame3.setTo(Scalar(0, 0, 0), 255 - mask);
	}
	else if (hue == 1) {
		inRange(frame3, V_lower, V_upper, mask);
		frame3.setTo(Scalar(0, 0, 0), 255 - mask);
	}
	else {

		inRange(frame3, R_lower, R_upper, mask);
		frame3.setTo(Scalar(0, 0, 0), 255 - mask);


	}


	cvtColor(frame3, frame4, CV_HSV2BGR);
	imshow("Color Mask", mask);
	imshow("Color Detection", frame4);
}

int main(int argc, const char** argv)
{

	cvtColor(frame1, frame2, CV_BGR2HSV);
	namedWindow("Color Mask", CV_WINDOW_AUTOSIZE);
	namedWindow("Color Detection", CV_WINDOW_AUTOSIZE);
	createTrackbar("Colors", "Color Detection", &hue, 2, callFunc);
	callFunc(0, 0);


	waitKey(0); //waits infinite amount of time for a keypress

	return 0;
}
