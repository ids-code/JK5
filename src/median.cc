#include <iostream>
#include <opencv2/core/core.hpp>              // OpevCVの基本機能(データ型)
#include <opencv2/imgproc/imgproc.hpp>        // OpenCVで画像処理
#include <opencv2/highgui/highgui.hpp>        // GUI のヘッダファイル
using namespace cv;
using namespace std;

#define	KMIN  9
#define	KMAX  15

int main(int argc, char* argv[]) {
  if (argc <= 1) {                            // コマンド引数の説明
    cerr << "usage: median <file>" << endl;
    return -1;                                // エラー終了
  }
  Mat sourceImage = imread(argv[1]);          // 画像ファイルの読込み
  if (!sourceImage.data) {                    // 読込みの成功確認
    cerr << "no such file: " << argv[1] << endl;
    return -1;                                // エラー終了
  }

  const string windowSource = "Source";       // 原画像ウィンドウ
  namedWindow(windowSource, CV_WINDOW_AUTOSIZE);// ウィンドウ生成
  imshow(windowSource, sourceImage);          // 原画像の表示
  const string windowGaussian = "Gaussian";   // Gausiian画像ウィンドウ
  namedWindow(windowGaussian, CV_WINDOW_AUTOSIZE);// ウィンドウ生成
  const string windowBox = "Box";             // box画像ウィンドウ
  namedWindow(windowBox, CV_WINDOW_AUTOSIZE); // ウィンドウ生成
  const string windowMedian = "Median";       // median画像ウィンドウ
  namedWindow(windowMedian, CV_WINDOW_AUTOSIZE);// ウィンドウ生成

  for (int ksize = KMIN; ksize <= KMAX; ksize +=2) {
    Mat resultImage;                          // 結果画像
    GaussianBlur(sourceImage, resultImage, Size(ksize, ksize), -1);
                                              // Gaussianフィルタリング
    imshow(windowGaussian, resultImage);      // Gaussian画像の表示
    boxFilter(sourceImage, resultImage, CV_8UC3, Size(ksize, ksize));
                                              // boxフィルタリング
    imshow(windowBox, resultImage);           // box画像の表示
    medianBlur(sourceImage, resultImage, ksize);
                                              // medianフィルタリング
    imshow(windowMedian, resultImage);        // median画像の表示
    resultImage.release();                    // 結果画像の解放
    waitKey(0);                               // キー入力待ち(無限)
  }

  sourceImage.release();                      // sourceImageの解放
  return 0;                                   // 正常終了
}
