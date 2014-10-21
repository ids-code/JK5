#include <iostream>
#include <opencv2/core/core.hpp>              // OpevCVの基本機能(データ型)
#include <opencv2/imgproc/imgproc.hpp>        // OpenCVで画像処理
#include <opencv2/highgui/highgui.hpp>        // GUI のヘッダファイル

#define TRACKBAR_MAX_VALUE 255
#define THRESHOLD_MAX_VALUE 255

using namespace cv;                           // OpenCV 名前空間
using namespace std;

const string windowName = "Binary";
Mat grayImage;
void onChange(int value, void* data);

int main(int argc, char* argv[]) {
  if (argc <= 1) {                            // コマンド引数の説明
    cerr << "usage: binary <file>" << endl;
    return -1;                                // エラー終了
  }
  Mat image = imread(argv[1]);                // 画像ファイルの読込み
  if (!image.data) {                          // 読込みの成功確認
    cerr << "no such file: " << argv[1] << endl;
    return -1;                                // エラー終了
  }
  
  cvtColor(image, grayImage, CV_BGR2GRAY);
  image.release();                            // imageの解放
  int value = 128;
  namedWindow(windowName, CV_WINDOW_AUTOSIZE);
  const string trackbarName = "Threshold";
  createTrackbar(trackbarName, windowName, &value, THRESHOLD_MAX_VALUE, onChange, NULL);
  imshow(windowName, grayImage);
  waitKey(0);
  grayImage.release();

  return 0;                                   // 正常終了
}

void onChange(int value, void* data){
  Mat binaryImage;
  threshold(grayImage, binaryImage, value, THRESHOLD_MAX_VALUE, THRESH_BINARY);
  imshow(windowName, binaryImage);
  binaryImage.release();
}