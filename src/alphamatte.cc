#include <iostream> //OpenCVの基本機能(データ型)
#include <opencv2/core/core.hpp>  //OpenCVで画像処理
#include <opencv2/imgproc/imgproc.hpp> //GUIのヘッダファイル
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
  if (argc < 4) { //コマンド引数の説明
    cerr << "usage: alphamatte <fore> <back> <alpha>" << endl;
    return -1; //エラー終了
  }
  Mat image = imread(argv[1]); //全景画像の読み込み
  if (!image.data) { //読み込みの成功確認
    cerr << "no such file: " << argv[1] << endl;
    return -1; //エラー終了
  }
   string window = "foreground"; //前景画像ウィンドウ
   namedWindow(window, CV_WINDOW_AUTOSIZE);
   imshow(window, image);  //前景画像の表示
   Mat foreImage(image.size(), CV_32FC3); //float型画像
   image.convertTo(foreImage, CV_32F); //前景画像の変換
   
   image = imread(argv[2]); //背景画像の読み込み
   if (!image.data) { //読み込みの成功確認
     cerr << "no such file: " << argv[2] << endl;
     return -1; //エラー終了
   }
   if ( (foreImage.rows != image.rows) ||
        (foreImage.cols != image.cols) ) { //2画像の大きさ比較
    cerr << "second image size is incompatible";
    return -1; //エラー終了
  }
    window = "background"; //背景画像ウィンドウ
    namedWindow(window, CV_WINDOW_AUTOSIZE);
    imshow(window, image); //前景画像の表示
    
    Mat backImage(image.size(), CV_32FC3); //float型変換
    image.convertTo(backImage, CV_32F); //背景画像の変換
    
    image = imread(argv[3]); //マスク画像の読み込み
    if (!image.data) { //読み込みの成功確認
     cerr << "no such file: " << argv[3] << endl;
     return -1; //エラー終了
   }
   if ( (foreImage.rows != image.rows) ||
          (foreImage.cols != image.cols) ) { // 2画像の大きさ比較
    cerr << "alphamatte size is incompatible";
      return -1; //エラー終了
    }
    window = "alpha"; //alphamatteウィンドウ
    namedWindow(window, CV_WINDOW_AUTOSIZE);
    imshow(window,image); //alphamatteの表示
    Mat alphaImage(image.size(), CV_32FC3); //float型画像
    image.convertTo(alphaImage, CV_32F, 1.0/255.0, 0.0); //alphamatteの変換(正規化)
    Mat onesImage(foreImage.size(), CV_32FC3, Scalar(1.0,1.0,1.0));
    //全チャネル1の画像
    foreImage = foreImage.mul(alphaImage); //前景の抽出
    backImage = backImage.mul(onesImage-alphaImage); //前景の抽出
    
    Mat resultImage = foreImage + backImage; //結果画像(前景と背景)
    resultImage.convertTo(image, CV_8U); //結果画像の変換
    window = "result"; //結果画像のウィンドウ
    namedWindow(window, CV_WINDOW_AUTOSIZE);
    imshow(window,image); //結果画像の表示
    waitKey(0); //キー入力待ち(無限)
    
    image.release(); //結果画像の解放
    resultImage.release(); //結果画像(合成)の解放
    foreImage.release(); //前景画像の解放
    backImage.release(); //背景画像の解放
    alphaImage.release(); //alphamatteの解放
    onesImage.release(); //全チャネル1の画像
    return 0; //正常終了
}