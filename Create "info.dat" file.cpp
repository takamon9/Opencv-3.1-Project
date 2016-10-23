#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
using namespace cv;

// You have to install OpenCv 2.4.x or later version 3.x to compile this code. 
// Also,info.dat shoud be saved by ANSI Code,not by unicode or UTF-8.
// In this code, your png image files put into the directory :"C:/numSets/num_0/pos/***.png"
// 0 as variable number.

int main(void) {

	string posFileName[1500];
	Mat posSrcImage[1500];
	Mat positiveImage[1500];
	string width, height;

	string fnum = "num_4"; //Change this num "num_x"
	int fileNumber = 234; //Input totall number of Files.

	ofstream ofs("C:/numSets/" + fnum + "/pos/info.dat");
	int a = 1;

	for (int i = 1; i < fileNumber + 1 ; i++) {  // input number of image files + 1

		stringstream ssname;
		stringstream ssrenamed;

		ssname << "C:/numSets/" + fnum + "/pos/num (" << a << ").png";

		string name = ssname.str();
		const char *cname = name.c_str();
		cout << cname << endl;

		ssrenamed << "C:/numSets/" + fnum + "/pos/" << a << ".png";

		string name2 = ssrenamed.str();
		const char *namerename = name2.c_str();
		cout << " to " << namerename << endl;

		rename(cname, namerename);

		a++;

		posFileName[i] = to_string(i) + ".png";
		posSrcImage[i] = imread("C:/numSets/" + fnum + "/pos/" + posFileName[i]);
		width = to_string(posSrcImage[i].size().width);
		height = to_string(posSrcImage[i].size().height);

		ofs << posFileName[i] + " 1 0 0 " + width + " " + height + "\n";

		cout << "info.dat file correctly created! Press Any Key to finish." << endl;
	}
	system("pause");
	return 0;
}

/*	void renameFunction (){

		string  str1("C:/numSets/num_0/pos/num0\(" + to_string(i) + ").png");
		const char *ptr1 = 0;
		ptr1 = str1.data();
		const char *c_str1 = str1.c_str();

		string  str2("C:/numSets/num_0/pos/" + to_string(i) + ".png");
		const char *ptr2 = 0;
		ptr2 = str2.data();
		const char *c_str2 = str2.c_str();

		cout << str1 << "==>"  << str2 << endl;
		//	cout << c_str1 << "\n" <<  c_str2 << endl;
		rename(c_str1, c_str2);

		//	delete(ptr1);
		//	delete(ptr2);
	
	}*/
