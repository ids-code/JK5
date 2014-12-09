#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#define MAX_VALUE 256

int value = MAX_VALUE / 2;
Mat image1;
Mat image2;
const string windowName = "Result";
void onChange(int value, void* data);

int main(int argc, char const *argv[])
{
	if (argc < 3)
	{
		cerr << "usage: dissolve <file1> <file2>" << endl;
		return -1;
	}
	image1 = imread(argv[1]);
	if (!image1.data)
	{
		cerr << "no such file:" << argv[2] << endl;
		return -1;
	}
	if ((image1.rows != image2.rows || image1.cols != image2.cols))
	{
		cerr << "image sizes are incompatible" << endl;
		return -1;
	}

	namedWindow(windowName, CV_WINDOW_AUTOSIZE);
	const string trackbarName = "Alpha";
	createTrackbar(trackbarName, windowName, &value, MAX_VALUE, onChange, NULL);
	onChange(value, NULL);
	waitKey(0);
	image1.release();
	image2.release();
	return 0;
}

void onChange(int value, void* data){
	double alpha = (double) value/MAX_VALUE;
	Mat resultImage = image1*(1.0-alpha) + image2*(alpha);
	imshow(windowName, resultImage);
	resultImage.release();
}