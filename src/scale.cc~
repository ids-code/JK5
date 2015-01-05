#include <iostream> //OpenCVの基本機能(データ型)
#include <opencv2/core/core.hpp>  //OpenCVで画像処理
#include <opencv2/imgproc/imgproc.hpp> //GUIのヘッダファイル
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

#define SCALE_X 0.5 //x軸方向の拡大縮小率
#define SCALE_Y 0.3 //y軸方向の拡大縮小率

int main(int argc, char* argv[]){
  if (argc < 2){ //コマンド引数の説明
    cerr << "usage: scale <sourceFile>" << endl;
	return -1; //エラー終了
	}
  Mat image = imread(argv[1]); //画像ファイルの読み込み
  if (!image.data) { //読み込みの成功確認
    cerr << "no such file: " << argv[1] << endl;
	return -1; //エラー終了
}

Size dsize(image.size().width*SCALE_X, image.size().height*SCALE_Y); //結果画像のサイズ
Mat destinationImage; //結果画像
resize(image, destinationImage, dsize, 0, 0, INTER_NEAREST); //最近隣補間

const string windowSource = "Source"; //原画像ウィンドウ生成
namedWindow(windowSource, CV_WINDOW_AUTOSIZE);
imshow(windowSource, image); //原画像の表示
const string windowDestination = "Destination"; //結果画像ウィンドウ生成

namedWindow(windowDestination,CV_WINDOW_AUTOSIZE);
imshow(windowDestination,destinationImage); //結果画像の表示
waitKey(0); //キー入力待ち(無限)
image.release(); //原画像の解放
destinationImage.release(); //結果画像の解放
return 0; //正常終了
}