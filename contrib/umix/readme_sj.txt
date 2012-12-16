-----
Unittest Multilingual Integrated Generation & Maintenance Environment
                                                          with XML
ユニットテストマルチ言語対応生成＆メンテナンス環境「X海亀」略して'umix'
-----

X海亀'umix'はxUnitによるユニットテストを支援するツールです。
umixはxUnitを利用したテストの雛形を生成します。またメソッドを追加することもできます。

●ソース版インストールの仕方

$DOWNLOAD_DIR/python/umix/へ移動したあと、

$ python setup.py install

と実行して下さい。DOSコンソールで使用される方はumix.batと/bin/umixの両方のファイル
をパスの通ったディレクトリにコピーして下さい。

●バイナリ版のインストール方法

解凍したディレクトリにパスを通すか、ディレクトリの中身をまるごと、パスの通った
ディレクトリにコピーして下さい。

●Rubyの例
  ○生成
$ umix -l ruby -s StringTest test1 test2 test3

RubyUnit用のテストコードを生成します。StringTestというクラスで
test1, test2, test3というメソッドを含みます。
  ○メソッド追加

$ umix -a stringtest.rb test4

test4を追加します。

●オプション
　○共有オプション
  --cout                 : ファイルを標準出力に出力
  --force,     -f        : 強制上書き
  --help,      -h        : ヘルプの表示
  --lang,      -l <Name> : 出力言語の設定
  --reference, -r        : 表明メソッドの簡易リファレンスを表示
  --version,   -v        : バージョン表示

  ○出力オプション
  --add,       -a <Name> : 既存のTestCaseにメソッドを追加
  --include,   -i <Name> : ファイルをインクルード/インポート
  --main,      -m <Name> : テスト実行ファイルを生成
  --prefix,    -P + / -  : 'test'プリフィックスを付加(デフォルト)
  --skeleton,  -s <Name> : テストスケルトンクラスを設定

Test::Unit(Ruby) (--lang ruby)
  サポートするオプション -a, -i, -m, -P, -r, -s
CppUnit (--lang cpp)
  サポートするオプション -a, -i, -m, -P, -r, -s
CppUnit-x (--lang cppx)
  サポートするオプション -a, -i, -m, -P, -r, -s
PyUnit (--lang python)
  サポートするオプション -a, -i, -m, -P, -r, -s
JUnit  (--lang java)
  サポートするオプション -a, -i, -P, -r, -s
JsUnit (--lang javascript)
  サポートするオプション -a, -i, -P, -r, -s
NUnit(C#) (--lang csharp)
  サポートするオプション -a, -i, -P, -r, -s
NUnit(VB.net) (--lang vbnet)
  サポートするオプション -a, -i, -P, -r, -s
NUnit(Managed C++) (--lang mcpp)
  サポートするオプション -a, -i, -P, -r, -s
Tcl/tk unit (--lang tcl)
  サポートするオプション -a, -i, -m, -P, -r, -s

●マルチリンガル対応
　○--langオプション
--lang(-l)オプションで言語を指定することができます。
今のところ、CppUnit(cpp)、CppUnit-x(cppx)、Ruby版Test::Unit(ruby)、JUnit(java)、
PyUnit(python), JsUnit(javascript), Tcl/tkユニット(tcl), NUnitのC#(csharp), 
VB.net(vbnet), Managed C++(mcpp)に対応しています。

$ umix --lang cpp
↑ CppUnit

　○簡易言語指定

こちらの方が簡単ですが、出力ファイル名の指定で拡張子を付けると各言語のフォーマット
でファイルを出力します。ただし、CppUnit-xは.cppx, Managed C++は.mcppです。

$ umix --skeleton TestString.py
↑ PyUnit

●テスト実行ファイル

CppUnit、CppUnit-xの場合は、一緒にビルドして下さい。CppUnit版であればcocuppaと
同じ実行時オプションが使用できます。

$ umix --lang cpp --main main --skeleton skeleton
$ c++ -lcppunit main.cpp skeleton.cpp

RubyUnit、PyUnitは、生成されたスクリプトのオプションでテストコードを指定します。

main.cpp、skeleton.cppを生成します。--forceオプションを付けないと、同名のファイル
が存在する場合はファイルは作成されません。

umixによって作成されたテストスケルトンはTestRegistyへの登録コードが含まれる
ため、引数にファイル名を指定するだけでテストを行うことができるようになります。

●スケルトンの出力

$ umix --skeleton StringTest test1 test2 ...

テストメソッドtest1, test2... が定義されたテストのスケルトン
stringtest.rbを作成します。同名のファイルが存在する場合は作成
されません。作成したテストは--mainで作成したスクリプトから実行
できるほか、単体でもテストを行うことができます。

$ ruby stringtest.rb

●リファレンスの表示

$ umix --reference java

表明メソッドの簡易リファレンスが表示されます。メソッドを忘れて
しまった場合にご利用下さい。けっこう便利です。
短縮系 -r javaも使用できます。

●既存のファイルにメソッドを追加

$ umix --add TestString.java testLength

既存のファイルに新しいテストを追加します。

●ちょっとした補足
　○テストの単体実行

C++版以外(Managed C++は除外)は生成されたテストケース単体で実行することができます。
JUnit版はオプション'a'を付けるとAWT版TestRunnerが、's'を付けるとSwing版TestRunner
で実行されます。

　○suite()メソッド

CppUnit、CppUnit-xの場合は常に生成されます（C++の運命)

他の、頭に'test'がついていると自動実行されるテスティングフレームワークの場合
は-Pオプションがついていると'test'が自動的に付加されて、suite()メソッドは
生成されません。-Pオプションがついていない場合はsuite()メソッドが生成されて
指定したテストメソッドが全て登録されます。

-----
History

2.1
- 名前をumigameからumixに変更
- 言語ごとの設定ファイルをXMLに変更。
- 処理系をPythonに変更。
- JsUnit対応(TNX 水越さん)
- Tcl/tkユニットに対応(TNX 安藤さん)
- NUnitのC#, VB.net, Managed C++に対応
- X海亀をハックしたい人向けにPDFでコラボレーション図を添付
  Pattern Weaverで書きました。
- py2exe対応
- --prefixオプションをデフォルトにした。
- --cinオプションの削除

2.0
- --addオプションの追加
- --referenceオプションの追加
- --namespace, --super, --abstruct, --separateオプションの削除
- 名前がcoppaからumigameに変更
- オプションが(-f && -s || -a)の時にはバックアップを残すようにした

1.7
- JUnit, CppUnit-x, PyUnitへ対応。
- cocuppaとcoruppaを統合。coppaへ。
- --main復活。TestRegistry利用のテストコードを出力
- --cin追加。stdinからの入力に対応。
- GetoptLongコードの除去。--cinに対応させるためにGetoptLongを廃止した。

1.5
- RubyUnit対応。RubyUnitのコードを吐くようにした
- --mainを廃止。ruby atest.rbと、実行時に渡されたときは自動的に
  　TestRunnerを呼ぶ
- 出力ファイルのサフィックスは.rbのみに変更
