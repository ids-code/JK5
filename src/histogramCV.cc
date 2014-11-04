#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#define HISTOGRAM_SIZE 256
#define HISTOGRAM_HEIGHT HISTOGRAM_SIZE
#define HISTOGRAM_WIDTH (HISTOGRAM_SIZE * 2)
#define TRACKBAR_HALF 100
#define TRACKBAR_MAX (TRACKBAR_HALF * 2)

const string windowNameResult = "Result";
const string windowNameHistogram = "Histogram";
Mat grayImage;
int trackbarBrightness = TRACKBAR_HALF;
int trackbarContrast = TRACKBAR_HALF;
void onChange(int value, void*data);

int main(int argc, char*argv[]){
  if (argc <= 1){
    cerr << "usage: histogram <file>" << endl;
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

  namedWindow(windowNameResult, CV_WINDOW_AUTOSIZE);

  const string trackbarNameBrightness = "Brightness";
  createTrackbar(trackbarNameBrightness, windowNameResult,
		 &trackbarBrightness, TRACKBAR_MAX, onChange);

  const string trackbarNameContrast = "Contrast";
  createTrackbar(trackbarNameContrast, windowNameResult,
		 &trackbarContrast, TRACKBAR_MAX, onChange);

  namedWindow(windowNameHistogram, CV_WINDOW_AUTOSIZE);

  onChange(TRACKBAR_HALF, NULL);
  waitKey(0);
  grayImage.release();
  return 0;
}

void onChange(int value, void* data){
  float bright = (float)trackbarBrightness / TRACKBAR_MAX;

  float delta = (float)(trackbarContrast - TRACKBAR_HALF) / TRACKBAR_HALF;

  float a,b;
  if (delta >= 0){
    a = 1.0 + delta;
    b = bright - 0.5*a;
  }
  else{
    a = 1.0 + delta; 
    b = bright - 0.5*a;
  }
  unsigned char lookUpTable[HISTOGRAM_SIZE];
  for (int orgVal = 0; orgVal < HISTOGRAM_SIZE; orgVal++){
    int newVal = round((a*orgVal/(HISTOGRAM_SIZE-1) + b)*(HISTOGRAM_SIZE-1));
    if (newVal < 0)
      newVal = 0;
    if (newVal > (HISTOGRAM_SIZE-1))
      newVal = (HISTOGRAM_SIZE-1);
    lookUpTable[orgVal] = (unsigned char)newVal;
  }
  Mat lookUpTableMatrix(HISTOGRAM_SIZE, 1, CV_8U, lookUpTable);

  Mat resultImage;
  LUT(grayImage, lookUpTableMatrix, resultImage);
  lookUpTableMatrix.release();
  imshow(windowNameResult, resultImage);

  MatND histogram;
  const Mat images[]    = {resultImage};
  const int channels[]  = {0};
  const int histSize[]  = {HISTOGRAM_SIZE};
  const float range_0[] = {0,HISTOGRAM_SIZE};
  const float* ranges[] = {range_0};
  calcHist(images, 1, channels, Mat(), histogram, 1, histSize, ranges, true, false);
  double maxValue = 0;
  minMaxLoc(histogram, NULL, &maxValue);
  histogram.convertTo(histogram, -1, HISTOGRAM_HEIGHT/maxValue, 0);
  int binWidth = round(((float)HISTOGRAM_WIDTH)/HISTOGRAM_SIZE);
  Mat histogramImage(HISTOGRAM_HEIGHT, HISTOGRAM_WIDTH, CV_8UC1, Scalar(255));
  for(int val = 0; val < HISTOGRAM_SIZE; val++){
    rectangle(histogramImage, Point(val*binWidth, HISTOGRAM_HEIGHT), 
	      Point(val*binWidth+1,
		    HISTOGRAM_HEIGHT-round(histogram.at<float>(val))),
	      Scalar(0), CV_FILLED);
  }
  imshow(windowNameHistogram, histogramImage);
  histogram.release();
  histogramImage.release();
  resultImage.release();
}
