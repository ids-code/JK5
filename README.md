this is page for info. engineering 5

openCVのインストール
macport, homebrewなど使うと簡単です。
xcode使いたいなら
jprogramer.com/opencva/522/

*以下，まだRakefile書いてません*
*Mac環境なのでclang++です*

$ rake setAlias
でcv++が動くようになります。（y先生のを拝借しただけなのでディレクトリ構成によっては動かないかもしれません。よくわからなかったら聞いてください。）

$ rake <filename>
で実行ファイルが作られます。

$ rake clean
でデバッグファイルを殺害します。

$ rake clobber
で実行ファイルとデバッグファイルを殺害します。