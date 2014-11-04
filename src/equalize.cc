#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]){
  if (argc <= 1){
    cerr << "usage: equalizeCV <file>" << endl;
    return -1;
  }
  Mat image = imread(argv[1]);
  if (!image.data){
    cerr << "no such file: " << argv[1] << endl;
    return -1;
  }
  Mat grayImage;
  cvtColor (image, grayImage, CV_BGR2GRAY);
  image.release();
  Mat equalizeImage;
  equalizeHist(grayImage, equalizeImage);

  const string windowNameGray = "Gray";
  namedWindow(windowNameGray, CV_WINDOW_AUTOSIZE);
  imshow(windowNameGray, grayImage);
  const string windowNameEqualize = "Equalize";
  namedWindow(windowNameEqualize, CV_WINDOW_AUTOSIZE);
  imshow(windowNameEqualize,equalizeImage);
  waitKey(0);
  grayImage.release();
  equalizeImage.release();
}
