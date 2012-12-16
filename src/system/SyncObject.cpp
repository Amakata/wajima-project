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
			// unlock(monitorLock)�ɂ���āA���̃X���b�h��monitorLock->notify()�����s�ł���悤�ɂ���B
			// �������AmonitorLock->notify()���ł�waitThreads.notify()���Ă�ł���B
			// ���������Ă��̐�Aunlock(*this)���s����܂Ŏ��ۂ�notify�͎��s����Ȃ��B
			SyncObject::Unlock unlock(monitorLock);
			{
				waitThreads_.push_back( Thread::getCurrentThread() );
				while( waitThreads_.end() != ::std::find( waitThreads_.begin() , waitThreads_.end() , Thread::getCurrentThread() ) ){
					Unlock unlock(*this);
					// ���ۂɂ�millisecond�͎��Ԃ��o�߂��邱�Ƃɂ���ĕω�����ׂ������A
					// �����ł͎��s�R�X�g���l���āA�����̃R�[�h�͒ǉ����Ȃ��B
					// notify���p�ɂɂ����Ȃ���R�[�h�ł͍ň��A��������wait���邱�ƂɂȂ�B
					// �������A���̂悤�Ȋm���͒Ⴂ�Ǝv����̂ŁA�����ł͂��̂悤�Ɏ�������B
					if( !waitSync_.wait( millisecond ) ){
						return false;
					}
				}
				// lock(*this)�ɂ���āA�J�����g�X���b�h�ȊO��reset��set���ł��Ȃ��B
				// ���������āA�m����1��notify��1��wait����������B
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