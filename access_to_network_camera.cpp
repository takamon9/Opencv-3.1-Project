#include <iostream>
#include <stdio.h>
#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**) {

	VideoCapture capture;
	Mat cap_image;

	string uname = "root";   // User name of Network Camera. Most of IP camera set username as "root" .
	string password = "abc123";   // Password of your Network Camera

	string ip_address = "http://" + uname + ":" + password + "@198.163.1.100/mjpg/video.mjpg";   // Input IP address of your Network Camera.Giving an example of Axis :/mjpg/video.mjpg

	if (capture.open(ip_address) == false) {
		cout << "Cannot connect IP camera! Check Your Camera Connection." << endl;
		return -1;
	}
	
	for (;;) {
		if (capture.read(cap_image) == false) {
			cout << "Cannot read capture image.Press any key." <<endl;
			waitKey();
		}
		imshow("Stream Viewer", cap_image);
		if (waitKey(1) >= 0) break;
	}
	return 0;
}
