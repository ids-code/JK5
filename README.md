this is page for info. engineering 5

openCVのインストール
macport, homebrewなど使うと簡単です。
xcode使いたいなら
jprogramer.com/opencva/522/

srcにソースファイルが入っています。
binはrakeを使うとバイナリとデバッグ情報が入るディレクトリです。

以下rake説明

*僕がMac環境なのでclang++です*

$ rake setAlias
でcv++が動くようになります。（y先生のを拝借しただけなのでディレクトリ構成によっては動かないかもしれません。よくわからなかったら聞いてください。） <- なりません，誰か教えてー

$ rake <name>
でsrcディレクトリに実行ファイルが作られます。
(<name>はソースの拡張子.ccを取ったものです。)
ex. rake binary

$ rake clobber
で実行ファイルとデバッグファイルを殺害します。