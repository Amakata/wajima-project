#include "window/Window.h"
#include "std/sys/Win32Assert.h"

namespace zefiro {
namespace window {

void Window::create(){
	WNDCLASSEX wndclass = { 0 };
	if( 0 == GetClassInfoEx( ::zefiro::application::ApplicationInitializer::getGHInstance() , opt_->getWndClassName().c_str() , &wndclass ) && isWindowClassName(opt_->getWndClassName()) ){
		wndclass.cbSize = sizeof(WNDCLASSEX);
		wndclass.lpfnWndProc= Window::gWndProc;
		wndclass.hInstance	= ::zefiro::application::ApplicationInitializer::getGHInstance();
		wndclass.hIcon = opt_->getIcon();
		wndclass.hCursor = opt_->getCursor();
		wndclass.hbrBackground = opt_->getBackgroundBrush();
		wndclass.lpszMenuName = opt_->getMenu();
		wndclass.lpszClassName = opt_->getWndClassName().c_str();
		wndclass.hIconSm =opt_->getIconSm();

		if( 0 == RegisterClassEx( &wndclass ) ){
			// TODO: ƒGƒ‰[ˆ—
			WIN32ASSERT(GetLastError());
		}
	}
	RECT rc = getSize(opt_->getWidth(),opt_->getHeight());
	hWnd_ = CreateWindowEx(
		opt_->getExStyle() ,
		opt_->getWndClassName().c_str() ,
		opt_->getCaption().c_str() ,
		opt_->getStyle() ,
		opt_->getX() ,
		opt_->getY() ,
		rc.right - rc.left ,
		rc.bottom - rc.top ,
		NULL ,
		NULL ,
		zefiro::application::ApplicationInitializer::getGHInstance() ,
		NULL ); 
	if( hWnd_ == NULL ){
		WIN32ASSERT(GetLastError());
	}
	SetWindowLongPtr( hWnd_ , GWL_USERDATA , reinterpret_cast<LONG_PTR>(this) );

}

void Window::release(){
}

void Window::update(){
	ShowWindow(hWnd_, zefiro::application::ApplicationInitializer::getGCmdShow());
	UpdateWindow(hWnd_);
}


LRESULT CALLBACK Window::gWndProc( HWND hWnd , UINT msg, WPARAM wParam, LPARAM lParam ){
	Window* window = reinterpret_cast<Window*>(GetWindowLongPtr( hWnd , GWL_USERDATA ));
	LRESULT result;
	if( window != NULL ){
		result = window->getMessageListeners().wndProc( hWnd , msg , wParam , lParam );
	}else{
		result = DefWindowProc( hWnd, msg, wParam, lParam);
	}
	return result;

}


}
}