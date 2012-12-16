#pragma once

#include <map>
#include "system/Thread.h"
#include "system/ThreadLocal.h"
#include "window/Window.h"
#include "std/win32debug_console_stream.h"
#include "loki/Singleton.h"

namespace zefiro {
namespace application {
class ApplicationBase : public zefiro::system::Thread {
	class ApplicationBases;
	typedef Loki::SingletonHolder<ApplicationBases> SingleApplicationBases;
public:
	ApplicationBase():quit_(false){
	}
	virtual ~ApplicationBase(){
	}
	zefiro::window::Window* getWindow(){
		return &window_;
	}
	virtual void run();
	virtual bool isQuit(){
		Lock lock(*this);
		return quit_;
	}
	virtual void setQuit( bool quit ){
		Lock lock(*this);
		quit_  = quit;
	}
	static ApplicationBase* getCurrentApplicationBase(){
		ApplicationBases& abs = SingleApplicationBases::Instance();
		return abs.getCurrentApplicationBase();
	}
protected:
	virtual bool pumpMessage( bool peek ){
		getWindow()->pumpMessage( peek );
		return !isQuit();
	}
	virtual void preCreate(){
	}
	virtual void postCreate(){
	}
	virtual void doRun();
	virtual void postDestory(){
	}
private:
	//	スレッドローカルにApplicatioBaseを管理する.
	class ApplicationBases {
		friend Loki::CreateUsingNew<ApplicationBases>;
	public:
		virtual ~ApplicationBases(){
		}
		void add( ApplicationBase* ab ){
			applicationBases_ = ab;
		}
		void del(){
			applicationBases_.clear();
		}
		ApplicationBase* getCurrentApplicationBase(){
			if( applicationBases_.empty() ){
				return NULL;
			}else{
				return applicationBases_;
			}
		}
	private:
		ApplicationBases(){
		}
		zefiro::system::ThreadLocal<ApplicationBase*> applicationBases_;
	};

	zefiro::window::Window window_;
	bool quit_;
};
}
}