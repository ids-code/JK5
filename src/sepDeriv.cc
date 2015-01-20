#include <iostream>
#include <opencv2/core/core.hpp> //OpenCVの基本構造(データ型)
#include <opencv2/imgproc/imgproc.hpp> //OpenCVで画像処理
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

  void printMatrix(Mat matrix){ //行列の表示
  cout << "(" << endl; //行列の表示開始
  for (int row = 0; row < matrix.rows; row++) {
    cout << "("; //行の先頭表示
	for ( int col = 0; col < matrix.cols; col++) {
	  cout << " " << matrix.at<float>(row,col) << ",";
	  }  //行列の各要素(float型)表示
	cout << ")" << endl; //行の末尾表示
	}
	cout << ")" << endl; //行の表示終了
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
	#define KERNEL_SIZE 3
	  Mat tmpImage; //float型結果画像(32FC1)
	  Mat krow; //行フィルタ行列
	  Mat kcol; //列フィルタ行列
	  getDerivKernels(krow, kcol, 1, 0, KERNEL_SIZE);
	    //分離フィルタ行列の作成,x方向は一階微分,y方向は0階微分
		sepFilter2D(grayImage, tmpImage, CV_32FC1, krow, kcol);
		  //分離フィルタ行列の適用
		convertScaleAbs(tmpImage, grayImage); //結果画像(絶対値 8UC1)
		cout << "row kernel matrix =" ;
		printMatrix(krow); //行フィルタ行列の表示
		cout << "column kernel matrix =";
		printMatrix(kcol); //列フィルタ行列の表示
	  
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