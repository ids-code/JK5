#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#define BASE 2.0
#define RATIO 32.0
#define HISTOGRAM_SIZE 256
#define TRACKBAR_HALF 128
#define TRACKBAR_MAX (TRACKBAR_HALF * 2)

Mat grayImage;
const string windowName = "Result";
int trackbarGamma = TRACKBAR_HALF;
unsigned char lookUpTable[TRACKBAR_MAX+1][HISTOGRAM_SIZE];

void changeGamma(int value, void* data);

int main(int argc, char* argv[]){
  if (argc <= 1){
    cerr << "usage: gammaCV <file>" << endl;
    return -1;
  }
  Mat image = imread(argv[1]);
  if (!image.data){
    cerr << "no such file: " << argv[1] << endl;
    return -1;
  }
  cvtColor (image, grayImage, CV_BGR2GRAY);
  image.release();
  const string windowNameGray = "Gray";
  namedWindow(windowNameGray, CV_WINDOW_AUTOSIZE);
  imshow(windowNameGray, grayImage);

  for (int trackbarVal = 0; trackbarVal <= TRACKBAR_MAX; trackbarVal++){
    double gamma = pow(BASE, (TRACKBAR_HALF - trackbarVal)/RATIO);
    for (int val = 0; val < HISTOGRAM_SIZE; val++){
      lookUpTable[trackbarVal][val] = (unsigned char)
	round(pow((double)val/(HISTOGRAM_SIZE-1), gamma)*(HISTOGRAM_SIZE-1));
    }
  }
  namedWindow(windowName, CV_WINDOW_AUTOSIZE);
  const string trackbarName = "Gamma";
  createTrackbar(trackbarName, windowName, &trackbarGamma,
		 TRACKBAR_MAX, changeGamma);
  changeGamma(TRACKBAR_HALF, NULL);
  waitKey(0);
  grayImage.release();
  return 0;
}

void changeGamma(int value, void* data){
  Mat lookUpTableMatrix(HISTOGRAM_SIZE, 1, CV_8U, lookUpTable[trackbarGamma]);
  Mat resultImage;
  LUT(grayImage, lookUpTableMatrix, resultImage);
  imshow(windowName, resultImage);
  lookUpTableMatrix.release();
  resultImage.release();
}
