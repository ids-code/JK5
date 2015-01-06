#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

Mat image_orig;
Mat image_moved;

#define MAX_VALUE 256
int value = MAX_VALUE / 2;

const string windowName = "Result";
void onChange(int value, void *data);

int
main(int argc, char *argv[])
{
  	if (argc < 2) 
  	{
    	cerr << "usage: en <file>" << endl;
		return -1;
	}
	image_orig = imread(argv[1]);
	if (!image_orig.data) 
	{
	  	cerr << "no such file: " << argv[1] << endl;
		return -1;
	}
	  
	Size size = image_orig.size();
	namedWindow(windowName, CV_WINDOW_AUTOSIZE);
	const string trackBarName ="Alpha";
	createTrackbar(trackBarName, windowName, &value, MAX_VALUE, onChange,NULL);


	Point2f orig[3];
	orig[0] = Point2f(0,0);
	orig[1] = Point2f(1, 0);
	orig[2] = Point2f(0, 1);
	Point2f moved[3];
	moved[0] = Point2f(1, 1);
	moved[1] = Point2f(2, 1);
	moved[2] = Point2f(1, 2);
	Mat matrix = getAffineTransform(orig, moved);
	warpAffine(image_orig, image_moved, matrix, size, INTER_CUBIC);

	onChange(value, NULL);
	waitKey(0);
	image_orig.release();
	image_moved.release();
	return 0;
}

void
onChange(int value, void *data)
{
 	double alpha = (double) value / MAX_VALUE;
 	image_orig.convertTo(image_orig, CV_32FC1);
 	image_moved.convertTo(image_moved, CV_32FC1);
	Mat resultImage = (image_orig - image_moved) * alpha;
 	image_orig.convertTo(image_orig, CV_8UC1);
 	image_moved.convertTo(image_moved, CV_8UC1);
	
	imshow(windowName, resultImage);
	resultImage.release();
}