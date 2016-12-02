#include <iostream>
#include <vector>
#include <opencv2\opencv.hpp>
#include <opencv2\ml\ml.hpp>
#include <iomanip>


using namespace std;
using namespace cv;
using namespace cv::ml;

int main()
{
	const int N_INPUT = 35;
	const int N_HIDDEN = 10;
	const int N_OUTPUT = 10;
	vector<int> layer_sizes = { N_INPUT, N_HIDDEN, N_OUTPUT };

	Ptr<ANN_MLP> neuron = ANN_MLP::create();
	neuron->setTrainMethod(ANN_MLP::RPROP);
	neuron->setLayerSizes(layer_sizes);
	neuron->setActivationFunction(ANN_MLP::SIGMOID_SYM, 0.66, 1);

	neuron->setTermCriteria(TermCriteria());

	Mat number_data = (Mat_<float>(10, 35) <<
		0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1,
		0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0,//0
		0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0,
		0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0,//1
		0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
		0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, //2
		0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0,
		0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, //3
		0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1,
		1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0,//4
		1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0,
		0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0,//5
		0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1,
		0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0,//6
		1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
		0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0,//7
		0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1,
		0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0,//8
		0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0,
		0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0//9
		);

	Mat training_image = Mat(Size(484, 94), CV_8UC1, Scalar(200));
	int p, q;
	Point pt1, pt2;
	int d;
	for(int j = 0;j<number_data.rows;j++)
		for (int i = 0; i < number_data.cols; i++)
		{
			p = i / 5;
			q = i % 5;
			pt1 = Point(20 + j * 45 + q * 8, 20 + p * 8);
			pt2 = Point(pt1.x + 5, pt1.y + 5);
			d = 255 * (1 - number_data.at<float>(j, i));
			rectangle(training_image, pt1, pt2, Scalar(d), -1);
		}
	imshow("訓練用データ", training_image);

	Mat teacher = Mat(Size(10, 10), CV_32F);
	for(int j = 0; j < teacher.rows ; j++)
		for (int i = 0; i < teacher.cols; i++)
		{
			if (i == j) teacher.at<float>(j, i) = 1.0f;
			else teacher.at<float>(j, i) = 0.0f;	
		}
	neuron->train(number_data, ROW_SAMPLE, teacher);

	Mat test_data;
	Mat results;
	cout << fixed << right;
	cout << endl;
	cout << "      RPROP ニューラルネットワーク出力				" << endl;
	cout << " 入力   0      1      2     3      4      5      6      7      8      9" << endl;
	for (int i = 0; i < N_OUTPUT; i++)
	{
		test_data = number_data.row(i);
		neuron->predict(test_data, results);
		cout << setw(3) << i << " ";
		for (int j = 0; j < N_OUTPUT; j++)
		{
			cout << setw(6) << setprecision(3) << results.at<float>(0, j) << " ";
		}
		cout << endl;

	}

	double Max_value;
	Point max_location;
	cout << fixed << right;
	cout << endl;
	cout << "入力   判定結果　　出力値" << endl;
	cout << "---- ---------- -------" << endl;
	for (int i = 0; i < N_OUTPUT; i++)
	{
		test_data = number_data.row(i);
		neuron->predict(test_data, results);
		minMaxLoc(results, 0, &Max_value, 0, &max_location);
		cout << setw(4) << i << "       " << max_location.x << "        " << Max_value << endl;
	}

	cout << endl;
	waitKey(0);
	destroyAllWindows();

	return 0;
}
