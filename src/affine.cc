#include <iostream> //OpenCVの基本機能(データ型)
#include <opencv2/core/core.hpp>  //OpenCVで画像処理
#include <opencv2/imgproc/imgproc.hpp> //GUIのヘッダファイル
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

int main(int argc, char* argv[]){
  if (argc < 2){ //コマンド引数の説明
    cerr << "usage: affine <sourceFile>" << endl;
	return -1; //エラー終了
	}
  Mat image = imread(argv[1]); //画像ファイルの読み込み
  if (!image.data) { //読み込みの成功確認
    cerr << "no such file: " << argv[1] << endl;
	return -1; //エラー終了
}

Size size = image.size(); //画像サイズ
Point2f original[3]; //変換前3点
original[0] = Point2f(0,0);
original[1] = Point2f(size.width, 0);
original[2] = Point2f(0, size.height);
Point2f translate[3]; //変換後3点
translate[0] = Point2f(100, 150);
translate[1] = Point2f(500, 50);
translate[2] = Point2f(50, 550);
Mat matrix = getAffineTransform(original,translate); //アフィン変換行列の作成

Mat destinationImage; //結果画像
warpAffine(image, destinationImage, matrix, size, INTER_CUBIC); //アフィン変換

const string windowSource = "Source"; //原画像ウィンドウ生成
namedWindow(windowSource, CV_WINDOW_AUTOSIZE);
imshow(windowSource, CV_WINDOW_AUTOSIZE); //原画像の表示
const string windowDestination = "Destination"; //原画像ウィンドウ生成
namedWindow(windowDestination, CV_WINDOW_AUTOSIZE);
imshow(windowDestination, destinationImage); //結果画像の表示

waitKey(0); //キー入力待ち(無限)
image.release(); //原画像の解放
destinationImage.release(); //結果画像の解放
return 0; //正常終了
}