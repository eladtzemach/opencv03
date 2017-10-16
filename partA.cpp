#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>

using namespace cv;
using namespace std;

//load image
Mat frame1 = imread("C:/.../images/Picture3.png", CV_LOAD_IMAGE_UNCHANGED);
Mat frame2;
int hue = 25;

//the function that is called when the tracker is moved
void callFunc(int, void*) {

	Mat frame3, frame4;
	cvtColor(frame1, frame3, CV_BGR2HSV);

	for (int i = 0; i<frame3.rows; i++)
	{
		for (int j = 0; j<frame3.cols; j++)
		{
			Vec3b &hsv = frame3.at<Vec3b>(i, j);
			int H = hsv.val[0]; //hue
			int S = hsv.val[1]; //saturation
			int V = hsv.val[2]; //value
			if (hsv[0] != hue) {
				hsv[0] = 0;
				hsv[1] = 0;
				hsv[2] = 0;
			}

		}
	}
	cvtColor(frame3, frame4, CV_HSV2BGR);
	imshow("Processed Hue", frame4);
}

int main(int argc, const char** argv)
{

	cvtColor(frame1, frame2, CV_BGR2HSV);
	namedWindow("HSV Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Processed Hue", CV_WINDOW_AUTOSIZE);
	imshow("HSV Image", frame2);
	createTrackbar("Value", "Processed Hue", &hue, 180, callFunc);
	callFunc(0, 0);


	waitKey(0); //waits infinite amount of time for a keypress
				

	return 0;
}
