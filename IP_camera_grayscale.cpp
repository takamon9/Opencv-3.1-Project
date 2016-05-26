#include <iostream>
#include <stdio.h>
#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**) {

	VideoCapture capture;
	Mat cap_image;
	Mat gray;

	string uname = "root";   // User name of Network Camera. Most of IP camera set username as "root" .
	string password = "abc123";   // Password of your Network Camera

	string ip_address = "http://" + uname + ":" + password + "@169.254.1.100/mjpg/video.mjpg";   // Input IP address of your Network Camera.

	if (capture.open(ip_address) == false) {
		cout << "Cannot connect IP camera! Check Your Camera Connection." << endl;
		waitKey();
		return -1;
	}

	for (;;){
		if (capture.read(cap_image) == false){
			return -1;
		}
		cvtColor(cap_image, gray, CV_RGB2GRAY);   //convert capture image into grayscale color
		equalizeHist(gray, gray);
		imshow("gray", gray);
		if (waitKey(1) >= 0) break;
	}
	return 0;
}
