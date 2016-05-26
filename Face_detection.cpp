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


int main(int argc, char *argv[])
{
	Mat first_img = imread("face.jpg");
	Mat grayscaleimage;
	imshow("first_img", first_img);

	CascadeClassifier face_cascade;
	vector<Rect> faces;
	
	if (face_cascade.load("./haarcascade_frontalface_alt.xml") == false) {  // Chek same .xml file exists in this project holder
		printf("cascade.load failed!! put the xml file into this project holder\n");
		waitKey();
		return -1;
        }

	cvtColor(first_img, grayscaleimage, CV_BGR2GRAY);
	equalizeHist(grayscaleimage, grayscaleimage);

	face_cascade.detectMultiScale(grayscaleimage, faces);
	imshow("second_img", grayscaleimage);

	face_cascade.detectMultiScale(grayscaleimage, faces);
	for (int i = 0; i < (int)faces.size(); i++)
	{
		Scalar color(0, 0, 255);
		Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
		Point pt2(faces[i].x, faces[i].y);

		rectangle(first_img, pt1, pt2, color, 1, 8, 0);

	}
	namedWindow("Detected Image", WINDOW_AUTOSIZE);
	namedWindow("Grayscale Image", WINDOW_AUTOSIZE);
	imshow("Detected Image", first_img);
	imshow("Grayscale Image", grayscaleimage);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
