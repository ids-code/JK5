#include <iostream> //OpenCVの基本機能(データ型)
#include <opencv2/core/core.hpp>  //OpenCVで画像処理
#include <opencv/imgproc/imgproc.hpp> //GUIのヘッダファイル
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

using namespace std;
using namespace cv;

#define MAX_VALUE 256 //トラックバーの最大値
int value = MAX_VALUE / 2; //トラックバーの初期値
Mat image1; //画像1
Mat image2; //画像2
const string windowName = "Result"; //ウィンドウ名
void onChange(int value, void* data); //コールバック関数

int main(int argc, char* argv[]) {
  if (argv < 3) { //コマンド引数の説明
    cerr << "usage: dissolve <file1><file2>" << endl;
	return -1; //エラー終了
	}
	image1 = imread(argv[1]); //画像ファイルの読み込み
	if (!image1.data) { //読み込みの成功確認
	  cerr << "no such file: " << argv[1] << endl;
	  return -1; //エラー終了
	  }
	 image2 = imread(argv[2]); //画像ファイルの読み込み
	 if (!image2.data) { //読み込みの成功確認
	   cerr << "no such file: "<< argv[2] << endl;
	   return -1; //エラー終了
	   }
	 if ( (image.rows != image2.rows) ||
	   (image1.cols != image2.cols) ) { //2画像の大きさ比較
	   cerr << "image sizes are incompatible";
	   return -1; //エラー終了
	  }
	  
	  namedWindow(windowName, CV_WINDOW_AUTOSIZE); //結果画像ウィンドウ生成
	  const string trackBarName ="Alpha"; //トラックバーの名前
	  createTrackbar(trackbarName, windowName, &value, MAX_VALUE,
	    onChange(value,NULL); //トラックバーの生成
	  waitKey(0); //キー入力待ち(無限)
	  image1.release(); //画像1の解放
	  image2.release(); //画像2の解放
	  return 0; //正常終了
	  }
	  
	  void onChange(int value, void* data) { //コールバック関数
	    double alpha = (double) value / MAX_VALUE; alpha値の計算
		Mat resultImage = image1*(1.0-alpha) + image2*(alpha); //結果画像
		
		imshow(windowName, resultImage); //結果画像の表示
		resultImage.release(); //結果画像の解放
		}