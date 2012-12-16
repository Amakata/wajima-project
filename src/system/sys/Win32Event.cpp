/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/sys/Win32Event.cpp,v 1.4 2002/11/04 16:29:09 ama Exp $
 */


#include <string>
#include <sstream>

#include "std/Assert.h"
#include "std/sys/Win32Assert.h"
#include "std/Logger.h"
#include "Win32Event.h"


namespace zefiro {
namespace system {
	Win32Event::Win32Event( bool initState  , bool manualReset , ::std::string name )
		:manualReset_(manualReset),name_(name),exist_(false),constructError_(0){
			ZEFIRO_LOG( "NORMAL" , "Win32Event::Win32Event( bool , bool , std::string ) Begin" + toString());
		if( name_ == ::std::string("") ){
			event_ = CreateEvent( NULL , manualReset , initState , NULL );
		}else{
			event_ = CreateEvent( NULL , manualReset , initState , name_.c_str() );
		}
		if( event_ == NULL ){
			constructError_ = GetLastError();
			ZEFIRO_LOG( "ERROR" , "Win32Event::Win32Event( bool , bool , std::string ) END" + toString());
			return;
		}
		if( GetLastError() == ERROR_ALREADY_EXISTS ){
			exist_ = true;
		}
		ZEFIRO_LOG( "NORMAL" , "Win32Event::Win32Event( bool , bool , std::string ) END" + toString());
	}
	Win32Event::~Win32Event(){
		ZEFIRO_LOG( "NORMAL" , "Win32Event::~Win32Event() Begin" + toString());
		if( isAvailable() ){
			CloseHandle( event_ );
		}
		ZEFIRO_LOG( "NORMAL" , "Win32Event::~Win32Event() End" + toString());
	}
	bool Win32Event::isAlreadyExist() const{
		ZEFIRO_LOG( "NORMAL" , "Win32Event::isAlreadyExist()" + toString());
		return exist_;
	}
	bool Win32Event::isAvailable() const{
		ZEFIRO_LOG( "NORMAL" , "Win32Event::isAvailable()" + toString());
		return event_ != NULL;
	}
	::std::string Win32Event::getName() const{
		ZEFIRO_LOG( "NORMAL" , "Win32Event::getName()" + toString());
		return name_;
	}
	void Win32Event::set() {
		ZEFIRO_LOG( "NORMAL" , "Win32Event::set() Begin" + toString());
		if( isAvailable() ){
			if( 0 == SetEvent( event_ ) ){
				ZEFIRO_LOG( "ERROR" , "Win32Event::set()" + toString());
				WIN32ASSERT(GetLastError());
			}
		}else{
			ZEFIRO_LOG( "ERROR" , "Win32Event::set()" + toString());
			WIN32ASSERT( constructError_ );
		}
		ZEFIRO_LOG( "NORMAL" , "Win32Event::set() End" + toString());
	}
	void Win32Event::reset() {
		ZEFIRO_LOG( "NORMAL" , "Win32Event::reset() Begin" + toString());
		if( isAvailable() ){
			if( 0 == ResetEvent( event_ ) ){
				ZEFIRO_LOG( "ERROR" , "Win32Event::reset()" + toString());
				WIN32ASSERT(GetLastError());
			}
		}else{
			ZEFIRO_LOG( "ERROR" , "Win32Event::reset()" + toString());
			WIN32ASSERT( constructError_ );
		}
		ZEFIRO_LOG( "NORMAL" , "Win32Event::reset() End" + toString());
	}
	void Win32Event::pulse() {
		ZEFIRO_LOG( "NORMAL" , "Win32Event::pulse() Begin" + toString());
		if( isAvailable() ){
			if( 0 == PulseEvent( event_ ) ){
				ZEFIRO_LOG( "ERROR" , "Win32Event::pluse()" + toString());
				WIN32ASSERT(GetLastError());
			}
		}else{
			ZEFIRO_LOG( "ERROR" , "Win32Event::pluse()" + toString());
			WIN32ASSERT( constructError_ );
		}
		ZEFIRO_LOG( "NORMAL" , "Win32Event::pulse() End" + toString());
	}
	bool Win32Event::wait( long milliseconds ) {
		ZEFIRO_LOG( "NORMAL" , "Win32Event::wait() Begin" + toString());
		if( isAvailable() ){
			DWORD result = WaitForSingleObject( event_ , milliseconds );
			switch( result ){
			case WAIT_TIMEOUT:
				// タイムアウトによるリターン
				ZEFIRO_LOG( "NORMAL" , "Win32Event::wait() End" + toString());
				return false;
			case WAIT_OBJECT_0:
				// 正常にwaitから解放された。
				ZEFIRO_LOG( "NORMAL" , "Win32Event::wait() End" + toString());
				return true;
			case WAIT_ABANDONED:
				// 所有権が放棄されたeventだった。
				ZEFIRO_LOG( "NORMAL" , "Win32Event::wait() End" + toString());
				return true;
			case WAIT_FAILED:
				ZEFIRO_LOG( "ERROR" , "Win32Event::wait() End" + toString());
				WIN32ASSERT( GetLastError() );
			default:
				// 不明なエラー
				ZEFIRO_LOG( "ERROR" , "Win32Event::wait()" + toString());
				WIN32ASSERT( GetLastError() );
			}
			ZEFIRO_LOG( "ERROR" , "Win32Event::wait()" + toString());
			return false;
		}else{
			//	eventオブジェクト生成時のエラー
			ZEFIRO_LOG( "ERROR" , "Win32Event::wait()" + toString());
			WIN32ASSERT( constructError_ );
			return false;
		}
	}
	::std::string Win32Event::toString() const {
		::std::ostringstream ostrstr;
		ostrstr << " Event Handle = "  << event_ << " , Event Name = " << name_ << " , Manual Reset = " << manualReset_ << " , Already Exist = " << exist_;
		return ostrstr.str();
	}
}
}