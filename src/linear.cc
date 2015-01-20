#include <iostream>
#include <opencv2/core/core.hpp> //OpenCVの基本構造(データ型)
#include <opencv2/imgproc/imgproc.hpp> //OpenCVで画像処理
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

void myFilter2D(Mat& src, Mat& dst, Mat& kernel) {
 if (dst.empty()) { //結果画像領域の確認
   dst.create(src.size(), kernel.type()); //結果画像領域の生成
   }
   int ahgt = kernel.rows / 2; //カーネルの縦半径
   int awth = kernel.cols / 2; //カーネルの横半径
   Mat org; //拡大原画像
   copyMakeBorder(src, org, ahgt, ahgt, awth, awth, BORDER_DEFAULT);
   //カーネル半径分だけ原画像を拡大する
   for (int drow = 0; drow < dst.rows; drow++) { //全ピクセル
     for (int dcol = 0; dcol < dst.cols; dcol++) {
	   float result = 0; //ピクセル値の初期化
	   for (int krow = 0; krow < kernel.rows; krow++) {
	     for (int kcol = 0; kcol< kernel.cols; kcol++) {
		   result += org.at<uchar>(drow+krow,dcol+kcol) * 
		     kernel.at<float>(krow,kcol);
			   //拡大原画像とカーネル係数の積和
			 }
		}
	 dst.at<float>(drow,dcol) = result; //結果画像への書き込み
	 }
	}
  }
  
  int main(int argc, char* argv[]) {
    if (argc <= 1) { //コマンド引数の説明
	  cerr <<"usage: linear <file>" << endl;
	  return -1;
	  }
	Mat sourceImage = imread(argv[1]); //画像ファイルの読み込み
	if (!sourceImage.data) { //読み込みの成功確認
	  cerr << "no such file: " << argv[1] << endl;
	  return -1; //エラー終了
	  }
	Mat grayImage; //同サイズの画像
	cvtColor(sourceImage, grayImage, CV_BGR2GRAY); //グレースケール変換
	
	//ここから空間フィルタリング
	float m[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
	//カーネル係数の定義
	Mat kernel(3,3,CV_32F,m); //カーネル係数行列
	Mat tmpImage; //float型結果画像(32FC1)
	myFilter2D(grayImage, tmpImage, kernel); //フィルタリング
	convertScaleAbs(tmpImage,grayImage); //結果画像(絶対値 8UC1)
	//ここまで空間フィルタリング
	
	const string windowSource = "Source"; //原画像ウィンドウ
	namedWindow(windowSource, CV_WINDOW_AUTOSIZE); //ウィンドウ生成
	imshow(windowSource, sourceImage); //原画像の表示
	const string windowResult ="Result"; //結果画像ウィンドウ
	namedWindow(windowResult,CV_WINDOW_AUTOSIZE); //ウィンドウ生成
	imshow(windowResult, grayImage); //結果画像の表示
	waitKey(0); //キー入力待ち(無限)
	sourceImage.release(); //sourceImageの解放
	grayImage.release(); //grayImageの解放
	tmpImage.release(); //tmoImageの解放
	return 0;
	}