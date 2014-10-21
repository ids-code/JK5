#include <iostream>
#include <opencv2/core/core.hpp>              // OpevCVの基本機能(データ型)
#include <opencv2/imgproc/imgproc.hpp>        // OpenCVで画像処理
#include <opencv2/highgui/highgui.hpp>        // GUI のヘッダファイル

using namespace cv;                           // OpenCV 名前空間
using namespace std;

int main(int argc, char* argv[]) {
  if (argc <= 1) {                            // コマンド引数の説明
    cerr << "usage: imageInfo <file>" << endl;
    return -1;                                // エラー終了
  }
  Mat image = imread(argv[1]);                // 画像ファイルの読込み
  if (!image.data) {                          // 読込みの成功確認
    cerr << "no such file: " << argv[1] << endl;
    return -1;                                // エラー終了
  }
  if (image.isContinuous())                   // データの連続性
    cout << "isContinuous() = true" << endl;  // ギャップなし
  else
    cout << "isContinuous() = false" << endl; // ギャップあり
  cout << "size of an element = " << image.elemSize() <<
    " Bytes" << endl;                         // 1画素のバイト数
  cout << "size of a channel  = " << image.elemSize1() <<
    " Bytes" << endl;                         // 1channelのバイト数
  cout << "type (hexadecimal) = " << hex << image.type() <<
    dec << endl;                              // 画素のフォーマット
  cout << "depth (hexadecimal) = " << hex << image.depth() <<
    dec << endl;                              // 1channelのフォーマット
  switch (image.depth()) {
  case CV_8U:  cout << " CV_8U" << endl; break; // 8byte uchar
  case CV_8S:  cout << " CV_8S" << endl; break; // 8byte char
  case CV_16U: cout << " CV_16U" << endl; break;// 16byte ushort
  case CV_16S: cout << " CV_16S" << endl; break;// 16byte short
  case CV_32S: cout << " CV_32S" << endl; break;// 32byte int
  case CV_32F: cout << " CV_32F" << endl; break;// 32byte float
  case CV_64F: cout << " CV_64F" << endl; break;// 64byte double
  defalut: cout << "    something else" << endl;// ありえない
  }
  cout << "size of a step    = " << image.step1() << endl;
                  // 1行(row)のバイト数 = cols * elemSize() + ギャップ
  cout << "no. of channels   = " << image.channels() << endl;
                                              // 1画素のchannel数
  cout << "no. of rows       = " << image.rows << endl;
                                              // 画像の行数
  cout << "no. of columns    = " << image.cols << endl;
                                              // 画像の列数
  namedWindow("Image", CV_WINDOW_AUTOSIZE);   // ウィンドウの生成
  imshow("Image", image);                     // imageの表示
  waitKey(0);                                 // キー入力待ち(無限)
  image.release();                            // imageの解放

  return 0;                                   // 正常終了
}
