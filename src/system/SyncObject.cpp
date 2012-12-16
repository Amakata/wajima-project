/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/SyncObject.cpp,v 1.8 2002/11/17 10:28:00 ama Exp $
 */
#include <algorithm>
#include <sstream>

#include "SyncObject.h"
#include "std/Logger.h"
#include "std/Assert.h"

namespace zefiro{
namespace system {
	SyncObject::WaitThreads::WaitThreads(){
		waitSync_.reset();
	}
	SyncObject::WaitThreads::~WaitThreads(){
	}
	void SyncObject::WaitThreads::notify(){
		Lock lock(*this);
		{
			if( waitThreads_.size() > 0 ){
				waitThreads_.erase( waitThreads_.begin() );
				waitSync_.set();
			}
		}
	}
	void SyncObject::WaitThreads::notifyAll(){
		Lock lock(*this);
		{
			if( waitThreads_.size() > 0 ){
				waitThreads_.erase( waitThreads_.begin() , waitThreads_.end() );
				waitSync_.set();
			}
		}
	}
	bool SyncObject::WaitThreads::wait( SyncObject &monitorLock , int millisecond ){
		Lock lock(*this);
		{
			// unlock(monitorLock)によって、他のスレッドがmonitorLock->notify()を実行できるようにする。
			// ただし、monitorLock->notify()内ではwaitThreads.notify()を呼んでいる。
			// したがってこの先、unlock(*this)が行われるまで実際にnotifyは実行されない。
			SyncObject::Unlock unlock(monitorLock);
			{
				waitThreads_.push_back( Thread::getCurrentThread() );
				while( waitThreads_.end() != ::std::find( waitThreads_.begin() , waitThreads_.end() , Thread::getCurrentThread() ) ){
					Unlock unlock(*this);
					// 実際にはmillisecondは時間が経過することによって変化するべきだが、
					// ここでは実行コストを考えて、それらのコードは追加しない。
					// notifyが頻繁におこなわれるコードでは最悪、無限時間waitすることになる。
					// しかし、そのような確率は低いと思われるので、ここではこのように実装する。
					if( !waitSync_.wait( millisecond ) ){
						return false;
					}
				}
				// lock(*this)によって、カレントスレッド以外はresetもsetもできない。
				// したがって、確実に1つのnotifyが1つのwaitを解除する。
				waitSync_.reset();
			}
		}
		return true;
	}

	SyncObject::SyncObject(): waitThreads_(){
		ZEFIRO_LOG( "NORMAL" , "SyncObject::SyncObject()" + toString());
	}
	SyncObject::~SyncObject(){
		ZEFIRO_LOG( "NORMAL" , "SyncObject::~SyncObject()" + toString());
	}
	void SyncObject::notify(){
		ZEFIRO_LOG( "NORMAL" , "SyncObject::notify() Begin" + toString());
		waitThreads_.notify();
		ZEFIRO_LOG( "NORMAL" , "SyncObject::notify() End" + toString());
	}
	void SyncObject::notifyAll(){
		ZEFIRO_LOG( "NORMAL" , "SyncObject::notifyAll() Begin" + toString());
		waitThreads_.notifyAll();
		ZEFIRO_LOG( "NORMAL" , "SyncObject::notifyAll() End" + toString());
	}
	void SyncObject::wait(){
		ZEFIRO_LOG( "NORMAL" , "SyncObject::wait() Begin" + toString());
		waitThreads_.wait( *this );
		ZEFIRO_LOG( "NORMAL" , "SyncObject::wait() End" + toString());
	}
	bool SyncObject::wait( int millisecond ){
		ZEFIRO_LOG( "NORMAL" , "SyncObject::wait( int ) Begin" + toString());
		bool result = waitThreads_.wait( *this , millisecond );
		ZEFIRO_LOG( "NORMAL" , "SyncObject::wait( int ) End" + toString());
		return result;
	}
	::std::string SyncObject::toString() const{
		return ::std::string();
	}	
}
}