#pragma once

#include <windows.h>
#include <list>
#include "resource.h"
#include "system/ThreadingModel.h"
#include "system/OwnershipPolicy.h"
#include "loki/SmartPtr.h"
#include "loki/Threads.h"

namespace zefiro {
namespace window {

class MessageListener {
public:
	virtual LRESULT wndProc( HWND hWnd , UINT msg, WPARAM wParam , LPARAM lParam ) = 0;
	virtual ~MessageListener(){}
};

class MessageListeners : public MessageListener , public zefiro::system::ObjectLevelCountedLockable<MessageListeners> {
public:
	typedef Loki::SmartPtr<MessageListener , zefiro::system::RefCountedMTAdj<zefiro::system::ObjectLevelCountedLockable>::RefCountedMT > ListenerSP;
protected:
	typedef ::std::list< ListenerSP > Listeners;
public:
	virtual ~MessageListeners(){
	}
	void add( ListenerSP listener ){
		Lock lock(*this);
		listeners_.push_back(listener);
	}
	void del( ListenerSP listener ){
		Lock lock(*this);
		Listeners::iterator end = listeners_.end();
		for( Listeners::iterator it = listeners_.begin() ; it != end ; ++it ){
			if( (*it) == listener ){
				listeners_.erase( it );
			}else{
				++it;
			}
		}
	}
	void clear(){
		Lock lock(*this);
		listeners_.erase( listeners_.begin() , listeners_.end() );
	}
	virtual LRESULT wndProc( HWND hWnd , UINT msg, WPARAM wParam , LPARAM lParam ){
		Lock lock(*this);
		Listeners::iterator it = listeners_.begin();
		Listeners::iterator end = listeners_.end();
		while( it != end ){
			LRESULT result = (*it)->wndProc( hWnd , msg , wParam , lParam );
			if( result != 0 ){
				return result;
			}
			++it;
		}
		return DefWindowProc(hWnd,msg,wParam,lParam);
	}
private:
	Listeners listeners_;
};


}
}