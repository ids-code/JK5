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
	
	//ここから空間フィルタリング
	#define KERNEL_SIZE 15
	#define SIGMA 2.5
	 Mat resultImage; //結果画像
	 Mat kernel = getGaussianKernel(KERNEL_SIZE, SIGMA, CV_32F);
	 //分離フィルタ行列の作成,標準偏差の指定(0でデフォルト)
	 sepFilter2D(sourceImage, resultImage, CV_8UC3, kernel, kernel);
	 //分離フィルタ行列の適用
	 cout << "kernel matrix = ";
	 printMatrix(kernel); //分離フィルタ行列の表示
	//ここまで空間フィルタリング
	
	const string windowSource = "Source"; //原画像ウィンドウ
	namedWindow(windowSource, CV_WINDOW_AUTOSIZE); //ウィンドウ生成
	imshow(windowSource, sourceImage); //原画像の表示
	const string windowResult ="Result"; //結果画像ウィンドウ
	namedWindow(windowResult,CV_WINDOW_AUTOSIZE); //ウィンドウ生成
	imshow(windowResult, resultImage); //結果画像の表示
	waitKey(0); //キー入力待ち(無限)
	sourceImage.release(); //sourceImageの解放
	resultImage.release(); //resultImageの解放
	return 0;
	}