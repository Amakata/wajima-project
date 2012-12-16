#pragma once

#include <windows.h>
#include <stack>
#include <string>
#include "std/sys/Win32Assert.h"
#include "loki/SmartPtr.h"
#include "application/ApplicationInitializer.h"
#include "window/MessageListener.h"



namespace zefiro {
namespace window {

class WindowOption{
public:
	WindowOption(
		::std::string wndClassName ="",
		HICON icon =NULL,
		HICON iconSm =NULL,
		HCURSOR cursor =NULL,
		HBRUSH backgroundBrush = NULL,
		LPTSTR menu = NULL,
		DWORD style = NULL,
		DWORD exStyle = NULL,
		::std::string caption ="",
		int x = CW_USEDEFAULT ,
		int y = 0,
		int width = CW_USEDEFAULT ,
		int height = 0
		)
	:style_(style),exStyle_(exStyle),caption_(caption),x_(x),y_(y),width_(width),height_(height),
	icon_(icon),iconSm_(iconSm),cursor_(cursor),backgroundBrush_(backgroundBrush),menu_(menu)
	{
	}
	virtual ~WindowOption(){
	}
	virtual DWORD getStyle() const {
		return style_;
	}
	virtual void setStyle( DWORD style ){
		style_ = style;
	}
	virtual DWORD getExStyle() const {
		return exStyle_;
	}
	virtual void setExStyle( DWORD exStyle ){
		exStyle_ = exStyle;
	}
	virtual ::std::string& getCaption(){
		return caption_;
	}
	virtual void setCaption( ::std::string caption ){
		caption_ = caption;
	}
	virtual ::std::string& getWndClassName(){
		return wndClassName_;
	}
	virtual void setWndClassName( ::std::string wndClassName ){
		wndClassName_ = wndClassName;
	}
	virtual int getX() const {
		return x_;
	}
	virtual void setX( int x ){
		x_ = x;
	}
	virtual int getY() const {
		return y_;
	}
	virtual void setY( int y ){
		y_ = y;
	}
	virtual int getWidth() const {
		return width_;
	}
	virtual void setWidth( int width ) {
		width_ = width;
	}
	virtual int getHeight() const {
		return height_;
	}
	virtual void setHeight( int height ){
		height_ = height;
	}
	virtual HICON getIcon() const {
		return icon_;
	}
	virtual void setIcon( HICON icon ){
		icon_ = icon;
	}
	virtual HICON getIconSm() const {
		return iconSm_;
	}
	virtual void setIconSm( HICON iconSm ){
		iconSm_ = iconSm;
	}
	virtual HCURSOR getCursor() const {
		return cursor_;
	}
	virtual void setCursor( HCURSOR cursor ) {
		cursor_ = cursor;
	}
	virtual HBRUSH getBackgroundBrush() const {
		return backgroundBrush_;
	}
	virtual void setBackgroundBrush( HBRUSH brush ){
		backgroundBrush_ = brush;
	}
	virtual LPTSTR getMenu() const {
		return menu_;
	}
	virtual void setMenu( LPTSTR menu ){
		menu_ = menu;
	}
private:
	DWORD style_;
	DWORD exStyle_;
	::std::string caption_;
	::std::string wndClassName_;
	int x_;
	int y_;
	int width_;
	int height_;
	HICON icon_;
	HICON iconSm_;
	HCURSOR cursor_;
	HBRUSH backgroundBrush_;
	LPTSTR menu_;
};



class Window {
public:
	Window():hWnd_(NULL){
	}
	virtual ~Window(){
		release();
	}
	void setWindowOption( ::std::auto_ptr<WindowOption> opt ){
		opt_ = opt;
	}
	void create();
	void release();
	void update();
	MessageListeners& getMessageListeners(){
		return listeners_;
	}
	HWND getHWnd() const{
		return hWnd_;
	}
	static void pumpMessage( bool peek ){
		MSG msg;
		if( peek ){
			while( 0 != PeekMessage(&msg, NULL, 0, 0,PM_REMOVE) ){
				if (!TranslateAccelerator(msg.hwnd, NULL, &msg)) 
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}else{
			while( 0 != GetMessage(&msg, NULL, 0, 0) ){
				if (!TranslateAccelerator(msg.hwnd, NULL, &msg)) 
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
	}
	static LRESULT CALLBACK gWndProc( HWND hWnd , UINT msg, WPARAM wParam, LPARAM lParam ); 
private:
	RECT getSize( int width , int height ){
		RECT result;
		::SetRect(&result,0,0,width,height);
		LONG style = opt_->getStyle();
		bool isUseMenu;
		if( opt_->getMenu() != NULL ){
			isUseMenu = true;
			style |= WS_SYSMENU;
		}else{
			isUseMenu = false;
			style &= ~WS_SYSMENU;	//	SYSMENUƒtƒ‰ƒO‚ðŠO‚·
		}
		if( FALSE == ::AdjustWindowRectEx(&result,style,isUseMenu,opt_->getExStyle()) ){
			WIN32ASSERT(GetLastError());
		}
		return result;
	}
	bool isWindowClassName( ::std::string name ){
		return true;
	}
	::std::auto_ptr<WindowOption > opt_;
	zefiro::window::MessageListeners listeners_;
	HWND hWnd_;
};

}
}