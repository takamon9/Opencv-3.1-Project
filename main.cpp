#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <fstream>

using namespace cv;
using namespace std;

int main(int, char**)
{

	VideoCapture capture;
	Mat original;
	Mat image;
	Mat gray;
	Mat cropNumberPlate;

	string uname = "root";   // User name of Network Camera. Most of IP camera set username as "root" .
	string password = "taka1974";   // Password of your Network Camera
	string ip_address = "http://" + uname + ":" + password + "@169.254.174.88/mjpg/video.mjpg";   // Input IP address of your Network Camera.

	if (capture.open(ip_address) == false) {
		cout << "Cannot connect IP camera! Check Your Camera Connection." << endl;
		system("pause");
		return -1;
	}

	vector<Rect> jpnNum;
	CascadeClassifier jpnNumPlate_cascade;
	if (jpnNumPlate_cascade.load("./cascade.xml") == false) {  // Chek same .xml file exists in this project holder
		printf("cascade.load failed!! put the xml file into this project holder\n");
		return -1;
	}

	for (;;)
	{
		if (capture.read(original) == false) {
			return -1;
		}
	
		Mat image = original.clone();
		cvtColor(original, gray, CV_BGR2GRAY);

		jpnNumPlate_cascade.detectMultiScale(gray, jpnNum,1.3,5);
		
		for (int i = 0; i < jpnNum.size(); i++)
		{
			Scalar color(0, 255, 255);
			Point pt1(jpnNum[i].x + jpnNum[i].width, jpnNum[i].y + jpnNum[i].height);
			Point pt2(jpnNum[i].x, jpnNum[i].y);
			rectangle(image, pt1, pt2, color, 2, 8, 0);
			Mat cropNumberPlate(original, Rect(pt1, pt2));
			imshow("captured number", cropNumberPlate);
			//imwrite("cropNumber.jpg", cropNumberPlate);
		}
		
		

		//imshow("grayscale_frame", gray);
		imshow("Detecting Number Plate Streaming", image);
		if (waitKey(1) >= 0) break;

	}
	destroyAllWindows;
	return 0;
}