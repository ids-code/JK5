#include <iostream>
#include <opencv2/core/core.hpp>              // OpevCVの基本機能(データ型)
#include <opencv2/imgproc/imgproc.hpp>        // OpenCVで画像処理
#include <opencv2/highgui/highgui.hpp>        // GUI のヘッダファイル
using namespace cv;
using namespace std;

#define	KSIZE        3                        // カーネルサイズ
#define	UPPER_THRESH 200                      // 上閾値(Canny)
#define	LOWER_THRESH 50                       // 下閾値(Canny)

int main(int argc, char* argv[]) {
  if (argc <= 1) {                            // コマンド引数の説明
    cerr << "usage: edge <file>" << endl;
    return -1;                                // エラー終了
  }
  Mat sourceImage = imread(argv[1]);          // 画像ファイルの読込み
  if (!sourceImage.data) {                    // 読込みの成功確認
    cerr << "no such file: " << argv[1] << endl;
    return -1;                                // エラー終了
  }
  Mat grayImage;                              // グレー画像
  cvtColor(sourceImage, grayImage, CV_BGR2GRAY);// グレー画像への変換
  sourceImage.release();                      // sourceImageの解放
  const string windowSource = "Source";       // 原画像ウィンドウ
  namedWindow(windowSource, CV_WINDOW_AUTOSIZE);
  imshow(windowSource, grayImage);            // 原画像(グレー)の表示

  Mat tmpImage;                               // float型結果画像(32FC1)
  Mat resultImage;                            // 結果画像(符号無)
  Sobel(grayImage, tmpImage, CV_32FC1, 1, 0, KSIZE);
  convertScaleAbs(tmpImage, resultImage);     // Sobelフィルタ(x方向)
  const string windowSobelX = "SobelX";       // Sobel画像ウィンドウ
  namedWindow(windowSobelX, CV_WINDOW_AUTOSIZE);
  imshow(windowSobelX, resultImage);          // Sobel画像の表示
  Sobel(grayImage, tmpImage, CV_32FC1, 0, 1, KSIZE);
  convertScaleAbs(tmpImage, resultImage);     // Sobelフィルタ(y方向)
  const string windowSobelY = "SobelY";       // Sobel画像ウィンドウ
  namedWindow(windowSobelY, CV_WINDOW_AUTOSIZE);
  imshow(windowSobelY, resultImage);          // Sobel画像の表示
  Laplacian(grayImage, tmpImage, CV_32FC1, KSIZE);
  convertScaleAbs(tmpImage, resultImage);     // Laplacianフィルタ
  const string windowLaplacian = "Laplacian"; // Laplacian画像ウィンドウ
  namedWindow(windowLaplacian, CV_WINDOW_AUTOSIZE);
  imshow(windowLaplacian, resultImage);       // Laplacian画像の表示
  Canny(grayImage, resultImage, LOWER_THRESH, UPPER_THRESH, KSIZE);
                                              // Cannyエッジ検出
  const string windowCanny = "Canny";         // Canny画像ウィンドウ
  namedWindow(windowCanny, CV_WINDOW_AUTOSIZE);
  imshow(windowCanny, resultImage);           // Canny画像の表示
  waitKey(0);                                 // キー入力待ち(無限) 
  grayImage.release();                        // grayImageの解放
  resultImage.release();                      // resultImageの解放
  return 0;                                   // 正常終了
}
