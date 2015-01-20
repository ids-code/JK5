#include <iostream>
#include <opencv2/core/core.hpp> //OpenCVの基本構造(データ型)
#include <opencv2/imgproc/imgproc.hpp> //OpenCVで画像処理
#include <opencv2/highgui/highgui.hpp> //GUIのヘッダファイル
using namespace cv;
using namespace std;

#define KSIZE 15 //カーネルサイズ
#define MAX_LEVEL 128 //トラックバーの最大値
int color = MAX_LEVEL; //色レベルの初期値
int space = MAX_LEVEL; //空間レベルの初期値
const string windowBilateral = "Bilateral"; //bilateral画像ウィンドウ
void onChange(int value, void* data); //コールバック関数
Mat sourceImage; //原画像

int main(int argc, char* argv[]) {
  if (argc <= 1) { //コマンド引数の説明
    cerr << "usage: bilateral <file>" << endl;
	return -1; //エラー終了
	}
  sourceImage = imread(argv[1]);  //画像ファイルの読み込み
  if (!sourceImage.data) { //読み込みの成功確認
    cerr << "no such file:" << argv[1] << endl;
	return -1; //エラー終了
	}
	
const string windowSource = "Source"; //原画像ウィンドウ
namedWindow(windowSource, CV_WINDOW_AUTOSIZE); //ウィンドウ生成
imshow(windowSource, sourceImage); //原画像の表示
const string windowGaussian = "Gaussian"; //Gaussian画像ウィンドウ
namedWindow(windowGaussian, CV_WINDOW_AUTOSIZE); //ウィンドウ生成
Mat gaussianImage; //Gaussian画像
GaussianBlur(sourceImage, gaussianImage, Size(KSIZE, KSIZE), 0); //Gaussianフィルタリング
imshow(windowGaussian, gaussianImage); //Gaussian画像の表示
gaussianImage.release(); //Gaussian画像の解放

namedWindow(windowBilateral, CV_WINDOW_AUTOSIZE); //ウィンドウ生成
const string trackbarColor = "ColorSigma"; //トラックバーの名前
createTrackbar(trackbarColor, windowBilateral, &color, MAX_LEVEL, onChange, NULL); //トラックバー生成
const string trackbarSpace = "SpaceSigma"; //トラックバーの名前
createTrackbar(trackbarSpace, windowBilateral, &space, MAX_LEVEL, onChange, NULL); //トラックバーの生成
onChange(color, NULL); //初期画面の表示
waitKey(0); //キー入力待ち(無限)
sourceImage.release(); //sourceImageの解放
return 0; //正常終了
}

void onChange(int value, void* data) { //コールバック関数
  Mat bilateralImage; //bilateral画像
  double sigmaColor = pow(2.0, color/12.0);  //色シグマ
  double sigmaSpace = space*space/512.0; //空間シグマ
  bilateralFilter(sourceImage, bilateralImage, KSIZE, sigmaColor, sigmaSpace); //bikateralフィルタリング
  imshow(windowBilateral, bilateralImage); //Birateral画像の表示
  bilateralImage.release(); //bilateral画像の解放
  }