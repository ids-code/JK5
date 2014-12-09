#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char const *argv[])
{
	if (argc < 4)
	{
		cerr << "usage: dissolve <fore> <back> <alpha>" << endl;
		return -1;
	}
	Mat image = imread(argv[1]);
	if (!image.data)
	{
		cerr << "no such file:" << argv[2] << endl;
		return -1;
	}
	string window = "foreground";
	namedWindow(window, CV_WINDOW_AUTOSIZE);
	imshow(window, image);
	Mat foreImage(image.size(), CV_32FC3);
	image.convertTo(foreImage, CV_32F);

	image = imread(argv[2]);
	if (!image.data)
	{
		cerr << "no such file: " << argv[2] << endl;
		return -1;
	}
	if ((foreImage.rows != image.rows) || (foreImage.cols != image.cols))
	{
		cerr << "second image size is incompatible" << endl;
		return -1;
	}
	window = "background";
	namedWindow(window, CV_WINDOW_AUTOSIZE);
	imshow(window, image);
	Mat backImage(image.size(), CV_32FC3);
	image.convertTo(backImage, CV_32F);

	image = imread(argv[3]);
		if (!image.data)
	{
		cerr << "no such file: " << argv[3] << endl;
		return -1;
	}
	if ((foreImage.rows != image.rows) || (foreImage.cols != image.cols))
	{
		cerr << "alpha image size is incompatible" << endl;
		return -1;
	}
	window = "alpha";
	namedWindow(window, CV_WINDOW_AUTOSIZE);
	imshow(window, image);
	Mat alphaImage(image.size(), CV_32FC3);
	image.convertTo(alphaImage, CV_32F, 1.0/255.0, 0.0);
	Mat onesImage(foreImage.size(), CV_32FC3, Scalar(1.0,1.0,1.0));
	foreImage = foreImage.mul(alphaImage);
	backImage = backImage.mul(onesImage - alphaImage);
	Mat resultImage = foreImage + backImage;
	resultImage.convertTo(image,CV_8U);
	window = "result";
	namedWindow(window, CV_WINDOW_AUTOSIZE);
	imshow(window, image);
	waitKey(0);

	image.release();
	foreImage.release();
	backImage.release();
	alphaImage.release();
	onesImage.release();
	return 0;
}
