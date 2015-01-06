#include <iostream>
#include <opencv2/core/core.hpp>              // OpevCVの基本機能(データ型)
#include <opencv2/imgproc/imgproc.hpp>        // OpenCVで画像処理
#include <opencv2/highgui/highgui.hpp>        // GUI のヘッダファイル
using namespace cv;
using namespace std;

#define KMIN 3                                // 最小カーネルサイズ
#define KMAX 41                               // 最大カーネルサイズ

void myBoxFilter(Mat& src, Mat& dest, Size ksize);
                                  // integral画像を用いたboxフィルタ関数

int main(int argc, char* argv[]) {
  if (argc <= 1) {                            // コマンド引数の説明
    cerr << "usage: box <file>" << endl;
    return -1;                                // エラー終了
  }
  Mat sourceImage = imread(argv[1]);          // 画像ファイルの読込み
  if (!sourceImage.data) {                    // 読込みの成功確認
    cerr << "no such file: " << argv[1] << endl;
    return -1;                                // エラー終了
  }
  const string windowSource = "Source";       // 原画像ウィンドウ
  namedWindow(windowSource, CV_WINDOW_AUTOSIZE);
  imshow(windowSource, sourceImage);          // 原画像の表示

  double tickFreqMS = getTickFrequency()/1000.0;// 時間定数
  cout << "tick frequency = " << tickFreqMS << "ticks/ms" << endl;
  Mat resultImage(sourceImage.size(), CV_8UC3); // 結果画像
  for (int ksize = KMIN; ksize <= KMAX; ksize+=2) {
                                              // カーネルサイズの変更
    cout << "Kernel Size = " << ksize << "x" << ksize << endl;
    Mat kernel = Mat(ksize, ksize, CV_32F, Scalar(1.0/(ksize*ksize)));
                                              // 2次元boxカーネルの作成
    Ptr<FilterEngine> filter =                // 2次元boxフィルタの作成
      createLinearFilter(CV_8UC3, CV_8UC3, kernel);
    int64 t = getTickCount();                 // 開始時刻
    filter->apply(sourceImage, resultImage);  // 2次元boxフィルタの適用
    cout << "filter2D:  " << (getTickCount()-t)/tickFreqMS << "ms\t";
                                              // 処理時間の表示
    kernel = Mat(ksize, 1, CV_32F, Scalar(1.0/ksize));
                                              // 1次元boxカーネルの作成
    t = getTickCount();                       // 開始時刻
    sepFilter2D(sourceImage, resultImage, CV_8UC3, kernel, kernel);
                                              // 分離boxフィルタの適用
    cout << "sepFilter: " << (getTickCount()-t)/tickFreqMS << "ms\t";
                                              // 処理時間の表示
    t = getTickCount();                       // 開始時刻
    boxFilter(sourceImage, resultImage, CV_8UC3, Size(ksize, ksize));
                                           // OpenCV box フィルタの適用
    cout << "boxFilter: " << (getTickCount()-t)/tickFreqMS << "ms\t";
                                              // 処理時間の表示
    t = getTickCount();                       // 開始時刻
    myBoxFilter(sourceImage, resultImage, Size(ksize, ksize));
                               // integral画像による box フィルタの適用
    cout << "myBoxFilter: " << (getTickCount()-t)/tickFreqMS << "ms" << endl;
                                              // 処理時間の表示
    const string windowResult = "Result";     // 結果画像ウィンドウ
    namedWindow(windowResult, CV_WINDOW_AUTOSIZE);
    imshow(windowResult, resultImage);        // 結果画像の表示
    waitKey(0);                               // キー入力待ち(無限)
  }
  sourceImage.release();                      // sourceImageの解放
  resultImage.release();                      // resultImageの解放
  return 0;                                   // 正常終了
}

void myBoxFilter(Mat& src, Mat& dst, Size ksize) {
  if (dst.empty()) {                          // データ領域の確認
    dst.create(src.size(),src.type());        // データ領域の作成
  }
  const int ahgt = ksize.height / 2;
  const int awth = ksize.width / 2;
  Mat org;
  copyMakeBorder(src, org, ahgt, ahgt, awth, awth, BORDER_DEFAULT);
                                  // カーネル半径分だけ原画像を拡大する
  Mat sum(org.rows+1, org.cols+1, CV_32SC3, Scalar(0,0,0));
  for (int row = 0; row < org.rows; row++) {  // integral 画像
    for (int col = 0; col < org.cols; col++) {// 全ピクセルについて
      sum.at<Vec3i>(row+1, col+1) = org.at<Vec3b>(row, col);
      sum.at<Vec3i>(row+1, col+1) +=
	(sum.at<Vec3i>(row, col+1) + sum.at<Vec3i>(row+1, col) -
	 sum.at<Vec3i>(row, col));            // integral 画像の生成
    }
  }
  // integral(org,sum,CV_32SC3);              // OpenCVの関数
  const float div  = 1.0 / ksize.area();      // カーネルサイズの逆数
  for (int row = 0; row < dst.rows; row++) {  // boxフィルタ
    for (int col = 0; col < dst.cols; col++) {// 全ピクセルについて
      Vec3f pix = sum.at<Vec3i>(row, col) -
	sum.at<Vec3i>(row, col+ksize.width) -
	sum.at<Vec3i>(row+ksize.height, col) +
	sum.at<Vec3i>(row+ksize.height, col+ksize.width);
      dst.at<Vec3b>(row, col) = pix * div;    // カーネルサイズで平均化
    }
  }
}
