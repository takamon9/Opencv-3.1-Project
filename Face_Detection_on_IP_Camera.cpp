
#include <iostream>
#include <stdio.h>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\cuda.hpp>
#include <windows.h>
#include <mmsystem.h>
#include <opencv2/objdetect/objdetect.hpp>

using namespace cv;
using namespace std;

int main(int, char**)
{

	VideoCapture capture;
	Mat image;
	Mat gray;

	char uname = "root";   // User name of Network Camera. Most of IP camera set username as "root" .
	char password = "abc123";   // Password of your Network Camera
	char ip_address = "http://" + uname + ":" + password + "@169.123.0.100/mjpg/video.mjpg";   // Input IP address of your Network Camera.

	if (capture.open(ip_address) == false) {
		cout << "Cannot connect IP camera! Check Your Camera Connection." << endl;
		waitKey();
		return -1;
	}

	vector<Rect> faces;
	CascadeClassifier face_cascade;
	if (face_cascade.load("./haarcascade_frontalface_alt.xml") == false) {  // Chek same .xml file exists in this project holder
		printf("cascade.load failed!! put the xml file into this project holder\n");
		return -1;
	}

	for (;;)
	{
			if (capture.read(image) == false){
			return -1;
			}

			cvtColor(image, gray, CV_BGR2GRAY);
			equalizeHist(gray, gray);

			face_cascade.detectMultiScale(gray, faces);
			for (int i = 0; i < (int)faces.size(); i++)
			{
				Scalar color(0, 0, 255);
				Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
				Point pt2(faces[i].x, faces[i].y);
				rectangle(image, pt1, pt2, color, 1, 8, 0);
    		}

			imshow("grayscale_frame", gray);
			imshow("Detecting Face Streaming", image);
			if (waitKey(1) >= 0) break;
    }
	return 0;
}
