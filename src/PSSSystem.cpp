// PSSSystem.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#pragma comment(lib, "cppunit.lib")
#pragma comment(lib, "lua.lib")
#pragma comment(lib, "tolua.lib")

#include "PSSSystem.h"

// このコード モジュールに含まれる関数の宣言を転送します :
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT	CALLBACK	CppUnitExecution(HWND, UINT, WPARAM, LPARAM);

class DefaultWindowOption : public zefiro::window::WindowOption {
public:
	DefaultWindowOption(){
		setWndClassName("DefaultWindowClass");
		setCaption("DefaultWindow");
		setStyle(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX );
		setIcon(LoadIcon(zefiro::application::ApplicationInitializer::getGHInstance(), (LPCTSTR)IDI_PSSSYSTEM));
		setIconSm(LoadIcon(zefiro::application::ApplicationInitializer::getGHInstance(), (LPCTSTR)IDI_SMALL));
		setCursor(LoadCursor(NULL, IDC_ARROW));
		setBackgroundBrush((HBRUSH)(COLOR_WINDOW+1));
		setMenu((LPTSTR)IDC_PSSSYSTEM);
		setExStyle(WS_EX_CLIENTEDGE);
		setX(0);
		setY(0);
		setWidth(800);
		setHeight(600);
	}
};

class PSSSystemMessageListener : public zefiro::window::MessageListener {
public:
	PSSSystemMessageListener( zefiro::application::ApplicationBase* ab ):ab_(ab){
	}
	virtual LRESULT wndProc( HWND hWnd , UINT msg, WPARAM wParam , LPARAM lParam ){
		int wmId, wmEvent;
		HDC hdc;
		PAINTSTRUCT ps;
		switch (msg) 
		{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// 選択されたメニューの解析 :
			switch (wmId)
			{
			case IDM_ABOUT:
				DialogBox(zefiro::application::ApplicationInitializer::getGHInstance(), (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				break;
			case IDM_CPPUNIT:
				DialogBox(zefiro::application::ApplicationInitializer::getGHInstance(), (LPCTSTR)IDD_CPPUNITBOX, hWnd ,(DLGPROC)CppUnitExecution);
				break;
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			default:
				return 0;
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: 描画コードをここに追加してください...
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			ab_->setQuit(true);
			PostQuitMessage(0);
			break;
		}
		return 0;
	}
private:
	zefiro::application::ApplicationBase* ab_;
};

class PSSSystem : public zefiro::application::ApplicationBase {
//protected:
public:
	virtual void preCreate(){
		getWindow()->setWindowOption( ::std::auto_ptr<zefiro::window::WindowOption>(new DefaultWindowOption()) );
		getWindow()->getMessageListeners().add(Loki::SmartPtr<zefiro::window::MessageListener , zefiro::system::RefCountedMTAdj<zefiro::system::ObjectLevelCountedLockable>::RefCountedMT >(new PSSSystemMessageListener(this) ) );
	}
	virtual void doRun();
private:
};


void PSSSystem::doRun(){
	zefiro::std::win32debug_console_stream wdcon;
	lua_State* luaState = lua_open();
	luaopen_base(luaState);
	luaopen_table(luaState);
	luaopen_io(luaState);
	luaopen_string(luaState);
	luaopen_math(luaState);
	luaopen_debug(luaState);
	luaopen_loadlib(luaState);
	tolua_open(luaState);
	tolua_zefiro_open(luaState);
	lua_dofile(luaState,"main.lua");
	lua_close( luaState );
	
/*
	::std::stringstream sstr;

	::std::ifstream ifs;
	ifs.open("test.png",::std::ios_base::in|::std::ios_base::binary);
	zefiro::graphics::Sprite sprite1(zefiro::graphics::ImageFactory::loadImage(ifs),0,0);
	ifs.close();
	ifs.open("test3.png",::std::ios_base::in|::std::ios_base::binary);
	zefiro::graphics::Sprite sprite3(zefiro::graphics::ImageFactory::loadImage(ifs),50,450);
	ifs.close();
//	Loki::SmartPtr<zefiro::graphics::Image> offscreen = zefiro::graphics::ImageFactory::create(800,600,zefiro::graphics::Color(zefiro::graphics::Color::X8R8G8B8));

	zefiro::input::KeyInput keyInput;
	keyInput.create();

	zefiro::input::MouseInput mouseInput;
	mouseInput.create();	

	Loki::SmartPtr<zefiro::graphics::GraphicsDevice> device(new zefiro::graphics::GraphicsDevice());
	device->create(0,800,600,zefiro::graphics::Color(zefiro::graphics::Color::X8R8G8B8),zefiro::graphics::Depth(zefiro::graphics::Depth::D32),true);

//	zefiro::std::FSPTimer timer;
//	timer.setFSP(60);

	int drawCount = 0;
	zefiro::std::Timer timer;
	timer.reset();
	Loki::SmartPtr<zefiro::graphics::Font> font(new zefiro::graphics::Font(16,"ＭＳ ゴシック",300));



	while( pumpMessage(true) ){
		sstr.str("");
		if( keyInput.getState() ){
			sstr << "key";
		}
		if( keyInput.isPress(DIK_ESCAPE) ){
			return;
		}
		if( mouseInput.getState() ){
		}
//		if(!timer.isSkip()){
			++drawCount;
//			sstr << "fps:" << timer.getRealFSP() << " 座標 x:"<< mouseInput.getX() << " y:" << mouseInput.getY();
			sstr << "fps:" << drawCount*1000/(timer.get()+1) << " 座標 x:"<< mouseInput.getX() << " y:" << mouseInput.getY();
			device->present();
			device->clear();
//			device->lock();
			zefiro::graphics::GraphicsConverter::blt(device,sprite1,zefiro::graphics::CopySinY(),zefiro::graphics::CopySinYParam(10,100));
			zefiro::graphics::GraphicsConverter::blt(device,sprite3,zefiro::graphics::AlphaAdd(),zefiro::graphics::AlphaAddParam());
//			zefiro::graphics::GraphicsConverter::blt(device,zefiro::graphics::Text(),zefiro::graphics::TextParam(255,0,0,sstr.str(),52,252,font,zefiro::graphics::TextParam::GRAY2));
//			zefiro::graphics::GraphicsConverter::blt(device,zefiro::graphics::Text(),zefiro::graphics::TextParam(255,0,0,sstr.str(),52,352,font,zefiro::graphics::TextParam::GRAY2));
			zefiro::graphics::GraphicsConverter::blt(device,zefiro::graphics::Text(),zefiro::graphics::TextParam(255,0,0,sstr.str(),52,452,font,zefiro::graphics::TextParam::GRAY2));
//			device->unlock();
//		}
//		timer.wait();	
	}*/
}


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	zefiro::std::win32debug_console_stream wdcon;
	zefiro::application::ApplicationInitializer applicationInitializer( hInstance , hPrevInstance , lpCmdLine , nCmdShow );
	try{
		zefiro::system::Thread* thread = new PSSSystem();
		thread->setJoinable(true);
		thread->start();
		thread->join();
	}catch( zefiro::std::Exception &e ){
		wdcon << e.what() << ::std::endl;
	}
	return 0;
}

// バージョン情報ボックスのメッセージ ハンドラです。
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}

LRESULT CALLBACK CppUnitExecution(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if(LOWORD(wParam) == IDOK){
			zefiro::std::win32debug_console_stream wdcon;
			CppUnit::TextUi::TestRunner runner;
			CppUnit::Outputter* outputter =
				CppUnit::CompilerOutputter::defaultOutputter(
					&runner.result(),wdcon
					);
			runner.setOutputter( outputter );
			runner.run();
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		if(LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}