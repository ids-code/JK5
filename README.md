## this is page for info. engineering 5

### openCVのインストール
macport, homebrewなど使うと簡単です。
xcode使いたいなら
jprogramer.com/opencva/522/

clangならrakeを書いたので下の方のrakeの使い方読むとおまじない関連の問題解決します。

----------------
以下rake説明

僕がMac環境なのでclang++です

--------------
### rakeよくわからない人向け

$ rake all
で全部コンパイルされます
binディレクトリに実行ファイルは入ります。

なんかうまくいかない場合は
$ rake clobber  
で実行ファイルとデバッグファイルを殺害します。

$ rake all01
ある回のものだけコンパイル(all02,all03などとします。)

------------
###その他

$ rake *filename*  
で個別コンパイル。
(<name>はソースの拡張子.ccを取ったものです。)
ex. rake binary

$ rake setAlias
も作りたいけどなんか動かない