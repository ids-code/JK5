#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const *argv[])
{
	if (argc <= 1)
	{
		cerr << "usage: grayscale <file>" << endl;
		return -1;
	}

	Mat image = imread(argv[1]);
	if (!image.data)
	{
		cerr << "no such filee: " << argv[1] << endl;
		return -1;
	}

	Mat grayImage;
	cvtColor(image, grayImage, CV_BGR2GRAY);
	const string fileName = "gray.jpg";
	imwrite(fileName, grayImage);
	string windowName = "Original";
	namedWindow(windowName, CV_WINDOW_AUTOSIZE);
	imshow(windowName, image);
	windowName = "Gray Image";
	namedWindow(windowName, CV_WINDOW_AUTOSIZE);
	imshow(windowName, grayImage);
	waitKey(0);
	image.release();
	grayImage.release();

	return 0;
}