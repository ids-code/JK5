#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#define BASE 2.0
#define RATIO 32.0
#define HISTGRAM_SIZE 256
#define TRACKBAR_HALF 128
#define TRACKBAR_MAX (TRACKBAR_HALF * 2)

Mat image;
const string windowName = "Result";
int buffer[3] = {TRACKBAR_HALF, TRACKBAR_HALF, TRACKBAR_HALF};

unsigned char lookUpTable[TRACKBAR_MAX+1][HISTGRAM_SIZE];

void chengeGamma(int value,void* data);

int main(int argc, char const *argv[])
{
	const string trackbarName[3] = {"X", "Y", "Z"};
	if (argc <= 1)
	{
		cerr << "usage: gammaXYZ <file>" << endl;
		return -1;
	}
	image = imread(argv[1]);
	if (!image.data)
	{
		cerr << "no such file: " << argv[1] << endl;
		return -1;
	}
	const string windowNameOrg = "Original";
	namedWindow(windowNameOrg, CV_WINDOW_AUTOSIZE);
	imshow(windowNameOrg, image);

	for (int i = 0; i < TRACKBAR_MAX; ++i)
	{
		double gamma = pow(BASE, (TRACKBAR_HALF - i)/RATIO);

		for (int j = 0; j < HISTGRAM_SIZE; ++j)
		{
			lookUpTable[i][j] = (unsigned char)
			  round(pow((double)j/(HISTGRAM_SIZE-1), gamma)*(HISTGRAM_SIZE-1));
		}
	}
	namedWindow(windowName, CV_WINDOW_AUTOSIZE);
	for (int i = 0; i < 3; ++i)
	{
		createTrackbar(trackbarName[i], windowName, &buffer[i], TRACKBAR_MAX, chengeGamma);
	}

	chengeGamma(TRACKBAR_HALF, NULL);
	waitKey(0);
	image.release();
	return 0;
}

void chengeGamma(int value, void* data){
	Mat imageXYZ;
	cvtColor(image, imageXYZ, CV_BGR2XYZ);
	vector<Mat> planes;
	split(imageXYZ, planes);
	for (int i = 0; i < 3; ++i)
	{
		Mat lookUpTableMatrix(HISTGRAM_SIZE, 1, CV_8U, lookUpTable[buffer[i]]);
		LUT(planes[i], lookUpTableMatrix, planes[i]);
		lookUpTableMatrix.release();
	}
	Mat result;
	merge(planes, imageXYZ);
	cvtColor(imageXYZ, result, CV_XYZ2BGR);
	imshow(windowName, result);
	for (int i = 0; i < 3; ++i)
	{
		planes[i].release();
	}
	imageXYZ.release();
	result.release();
}