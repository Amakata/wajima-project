プロジェクトの概要：P.S.S.System(Picture Story Show System)

プロジェクトの準備：
1.DirectX9
 http://www.microsoft.com/japan/msdn/directx/downloads.asp の
 a.DirectX 9.0b ソフトウェア開発キット (SDK)をダウロードしてインストールする。
  基本的にデフォルトインストールでよい。
  (デフォルトインストールではC:\DXSDKにインストールされる。)
  
 b.VisualStudio.NET 2003にDirectX9を登録する。
   1)VisualStudio.NETを起動する。
   2)メニュー->ツール->オプション->プロジェクトを選択する。
    プラットフォーム:Win32
    ディレクトリを表示するプロジェクト:インクルードファイル
    新しいディレクトリC:\DXSDK\INCLUDEを追加する。
   3)メニュー->ツール->オプション->プロジェクトを選択したまま。
    プラットフォーム:Win32
    ディレクトリを表示するプロジェクト:ライブラリファイル
    新しいディレクトリC:\DXSDK\LIBを追加する。
2.ActivePython
 1)
 http://www.activestate.com/ の
 Downloads -> ActivePyton -> Downloadを選択して、
 メールアドレス、氏名、会社名を入力して
 Windows用ActivePythonをダウンロードする。
 2)
 ダウンロードしたActivePythonのmsiを実行する。
 デフォルトの設定でインストールする。
3.py2exe
 1)
 http://sourceforge.net/projects/py2exe/ の
 Downloadを選択して、
 py2exe-0.4.1.win32-py2.2.exeをダウンロードする。(なければ、py2.2の別のバージョンを)
 2)
 ダウンロードした、 py2exe-0.4.1.win32-py2.2.exeを実行し、
 デフォルトの設定でインストールする。
 
4.X海亀
 1)
 プロジェクトのディレクトリ以下のcontrib\cuppa-?.?.?.zipを解凍する。(?はバージョン番号が入る)
 2)
 スタートメニューのアクセサリのコマンドプロンプトを開き。
 cd [プロジェクトのディレクトリ]\contrib\cuppa-?.?.?\python\umix
 と入力し実行して、プロジェクトのディレクトリ以下のcontrib\cuppa-?.?.?\python\umixへ移動する。
 ([プロジェクトのディレクトリ]には自分がプロジェクトを置いているディレクトリを指定する。)
 setup.py install
 と入力し実行する。
 setupwin.py install
 と入力し実行する。
 3)
 パスの通ったディレクトリにcontrib\umix\bin\umixをコピーし、umix.pyと名前を変更する。
 パスの通ったディレクトリにcontrib\libumixをディレクトリごとコピーする。
 
5.利用ソースのバージョン
cppunit 1.9.10
zlib 1.1.4
libpng 1.2.5
lua 5.0