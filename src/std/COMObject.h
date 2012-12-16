#pragma once
#include "system/Thread.h"
#include "loki/Singleton.h"
#include "system/ThreadingModel.h"
#include "system/ThreadLocal.h"
#include "std/sys/Win32Assert.h"
#include "std/win32debug_console_stream.h"
#include <oleauto.h>

namespace zefiro {
namespace std {

class Win32COM : public zefiro::system::ClassLevelCountedLockable<Win32COM> {	
public:
	typedef Loki::SingletonHolder<Win32COM> SingleWin32Com;
	virtual ~Win32COM(){
	}
	void init(){
		Lock lock(*this);
		if( count_.empty() || count_ == 0 ){
			count_ = 0;
			HRESULT result = ::CoInitialize(NULL); 
			if( S_OK != result ){
				WIN32ASSERT(result);
			}
		}
		count_ = count_ + 1;
	}
	void shutdown(){
		Lock lock(*this);
		if( count_.empty() ){
			return;
		}
		count_= count_-1;
		if( count_ == 0 ){
			::CoUninitialize();
		}
	}
protected:
	friend Loki::CreateUsingNew<Win32COM>;
	Win32COM(){
	}
private:
	zefiro::system::ThreadLocal<int> count_;
};

template <class T>
class COMObject {
public:
	COMObject():obj_(NULL),comInit_(false){
	}
	virtual ~COMObject(){
		release();
	}
	void create(REFCLSID clsid,REFIID guid){
		if( NULL == obj_ ){
			Win32COM& com = Win32COM::SingleWin32Com::Instance();
			com.init();
			comInit_ = true;
			release();
			HRESULT result = ::CoCreateInstance(clsid,NULL,CLSCTX_INPROC_SERVER,guid,(LPVOID*)&obj_);
			if( FAILED(result) ){
				obj_ = NULL;
				com.shutdown();
				WIN32ASSERT(result);
			}
		}
	}
	T* get()const{
		return obj_;
	}
	void set( T* obj ){
		if( NULL == obj_ ){
			obj_ = obj;
		}
	}
	bool empty() const{
		return obj_ == NULL;
	}
	void release(){
		if( NULL != obj_ ){
			obj_->Release();
			obj_ = NULL;
			if( comInit_ ){
				Win32COM& com = Win32COM::SingleWin32Com::Instance();
				com.shutdown();
				comInit_ = false;
			}
		}
	}
	T& operator*() const  {return *obj_; }
	T* operator->() const {return obj_; }
private:
	bool comInit_;
	T* obj_;
};


}
}