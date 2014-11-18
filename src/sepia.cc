#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#define DEFAULT_H 22
#define DEFAULT_S 150

int main(int argc, char const *argv[])
{
	if (argc <= 1)
	{
		cerr << "usage: sepia <file> " << endl;
		return -1;
	}
	Mat image = imread(argv[1]);
	if (!image.data)
	{
		cerr << "no such file: " << argv[1] << endl;
		return -1;
	}
	Mat imageHSV;
	cvtColor(image, imageHSV, CV_BGR2XYZ);
	std::vector<Mat> planes;
	split(imageHSV, planes);
	planes[0] = DEFAULT_H;
	planes[1] = DEFAULT_S;
	merge(planes, imageHSV);
	Mat sepiaImage;
	cvtColor(imageHSV, sepiaImage, CV_XYZ2BGR);
	imageHSV.release();

	const string windowNameSource = "Source";
	namedWindow(windowNameSource, CV_WINDOW_AUTOSIZE);
	imshow(windowNameSource, image);
	const string windowNameSepia = "Sepia";
	namedWindow(windowNameSepia, CV_WINDOW_AUTOSIZE);
	imshow(windowNameSepia, sepiaImage);
	waitKey(0);
	image.release();
	sepiaImage.release();
	return 0;
}