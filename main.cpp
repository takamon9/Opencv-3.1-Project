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
	Mat gray, grayNP;
	Mat cropNumberPlate,resizedNP,commercialPlate;

	string uname = "root";
	string password = "taka1974";
	string ip_address = "http://" + uname + ":" + password + "@169.254.58.10/mjpg/video.mjpg";

	if(!capture.open(ip_address));
	{
		cout << "Cannot connect IP camera! Check Your Camera Connection." << endl;
		system("pause");
		return -1;
	}

	vector<Rect> jpnNum;
	CascadeClassifier jpnNumPlate_cascade;
	if (jpnNumPlate_cascade.load("./700_cascade.xml")==false) { 
		cout << "cascade.load failed!! put the xml file into this project holder\n";
		return -1;
	}

	vector<Rect> commNum;
	CascadeClassifier jpnCommercialNum_cascade;
	if (!jpnCommercialNum_cascade.load("./num4_cascade.xml")){
		cout << "cannot read xml file.check out project holder" << endl;
		system("pause");
		return -1;
	}

	Scalar colorNum(0, 255, 0);
	Scalar colorComm(255, 255, 0);

	for (;;)
	{
		if (capture.read(original) == false) {
			return -1;
		}
	
		Mat image = original.clone();
		cvtColor(original, gray, CV_BGR2GRAY);

		jpnNumPlate_cascade.detectMultiScale(gray, jpnNum,1.27,5);
	
		for (int i = 0; i < jpnNum.size(); i++)
		{
			Point pt1(jpnNum[i].x + jpnNum[i].width, jpnNum[i].y + jpnNum[i].height);
			Point pt2(jpnNum[i].x, jpnNum[i].y);
			rectangle(image, pt1, pt2, colorNum, 2, 8, 0);
			Mat cropNumberPlate(original, Rect(pt1, pt2));

			resize(cropNumberPlate, resizedNP, Size(200, 100), 1.0, 1.0, INTER_LINEAR); //resize(src,dst,size(x,y),x_scale_factor,y_scale_factor,interpolation_type)
			cvtColor(resizedNP, grayNP, CV_BGR2GRAY);

			jpnCommercialNum_cascade.detectMultiScale(grayNP, commNum, 1.4, 5);

			for (int j = 0; j < commNum.size(); j++) {
				Point cpt1(commNum[j].x + commNum[j].width, commNum[j].y + commNum[j].height);
				Point cpt2(commNum[j].x, commNum[j].y);
				rectangle(resizedNP, cpt1, cpt2, colorComm, 2, 8, 0);
				cout << "4" << endl;
			}
		
			

			imshow("captured number", resizedNP);
			//imwrite("cropNumber.jpg", cropNumberPlate);
		} 
  /*
		jpnCommercialNum_cascade.detectMultiScale(gray, commNum, 1.4, 5);

		for (int j = 0; j < commNum.size(); j++) {
			Point cpt1(commNum[j].x + commNum[j].width, commNum[j].y + commNum[j].height);
			Point cpt2(commNum[j].x, commNum[j].y);
			rectangle(image, cpt1, cpt2, colorComm, 2, 8, 0);
			Mat commercialPlate(original, Rect(cpt1, cpt2));
			imshow("captured commercial number", commercialPlate);
		}
//  */

		//imshow("grayscale_frame", gray);
		imshow("Detecting Number Plate Streaming", image);
		if (waitKey(1) >= 0) break;

	}

	destroyAllWindows;

	return 0;
}