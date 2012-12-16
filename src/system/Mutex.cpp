/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/Mutex.cpp,v 1.4 2002/11/04 16:29:19 ama Exp $
 */

#include "Mutex.h"
#include "std/Logger.h"

#include <sstream>

namespace zefiro {
namespace system {
	Mutex::Mutex(){
		ZEFIRO_LOG( "NORMAL" , "Mutex::Mutex() Begin"+ toString());
		InitializeCriticalSection( &criticalSection_ );
		ZEFIRO_LOG( "NORMAL" , "Mutex::Mutex() End"+ toString());
	}
	Mutex::~Mutex(){
		ZEFIRO_LOG( "NORMAL" , "Mutex::~Mutex() Begin"+ toString());
		DeleteCriticalSection( &criticalSection_ );
		ZEFIRO_LOG( "NORMAL" , "Mutex::~Mutex() End"+ toString());
	}
	void Mutex::lock(){
		ZEFIRO_LOG( "NORMAL" , "Mutex::lock() Begin"+ toString());
		EnterCriticalSection( &criticalSection_ );
		ZEFIRO_LOG( "NORMAL" , "Mutex::lock() End" + toString());
	}
	void Mutex::unlock(){
		ZEFIRO_LOG( "NORMAL" , "Mutex::unlock() Begin" + toString());
		LeaveCriticalSection( &criticalSection_ );
		ZEFIRO_LOG( "NORMAL" , "Mutex::unlock() End" + toString());
	}
	::std::string Mutex::toString() const {
		::std::ostringstream ostrstr;
		ostrstr << " Mutex Pointer = " << this;
		return ostrstr.str();
	}
}
}