#pragma once

#include <windows.h>
#include "loki/Singleton.h"

namespace zefiro {
namespace application {

class ApplicationInitializer {
	typedef Loki::SingletonHolder< ApplicationInitializer > SingleApplicationInitializer;
public:
	ApplicationInitializer(){
	}
	ApplicationInitializer(
		HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPTSTR    lpCmdLine,
		int       nCmdShow 
		):hInstance_(hInstance),hPrevInstance_(hPrevInstance),lpCmdLine_(lpCmdLine),nCmdShow_(nCmdShow){
			SingleApplicationInitializer::Instance() = *this;
	}
	HINSTANCE getHInstance() const {
		return hInstance_;
	}
	HINSTANCE getPrevHInstance() const {
		return hPrevInstance_;
	}
	LPTSTR	getCmdLine() const {
		return lpCmdLine_;
	}
	int	getCmdShow() const {
		return nCmdShow_;
	}
	static HINSTANCE getGHInstance() {
		return SingleApplicationInitializer::Instance().getHInstance();
	}
	static HINSTANCE getGPrevHInstance() {
		return SingleApplicationInitializer::Instance().getPrevHInstance();
	}
	static LPTSTR getGCmdLine() {
		return SingleApplicationInitializer::Instance().getCmdLine();
	}
	static int getGCmdShow() {
		return SingleApplicationInitializer::Instance().getCmdShow();
	}
private:
	HINSTANCE	hInstance_;
	HINSTANCE	hPrevInstance_;
	LPTSTR		lpCmdLine_;
	int			nCmdShow_;

};
}
}

