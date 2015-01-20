#include <iostream>
#include <opencv2/core/core.hpp> //OpenCVの基本構造(データ型)
#include <opencv2/imgproc/imgproc.hpp> //OpenCVで画像処理
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
  
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
	#define KERNEL_SIZE 3
	Mat tmpImage; //float型結果関数(32FC1)
	Sobel(grayImage, tmpImage, CV_32F, 1, 0, KERNEL_SIZE);
	//Sobel Filterの適用,x方向は1階微分,y方向は0階微分
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