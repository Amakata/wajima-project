/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/SyncObject.h,v 1.5 2002/11/17 10:27:59 ama Exp $
 */

#ifndef __SYNCOBJECT_H__
#define __SYNCOBJECT_H__

#include <vector>
#include <string>

#include "Mutex.h"
#include "sys/Win32Event.h"
#include "Thread.h"
#include "ThreadingModel.h"

namespace zefiro {
namespace system {
	/**
	 *	同期オブジェクト。
	 *	スレッド間での同期をとるためのオブジェクトである。
	 *	同期や排他を行いたいオブジェクトはこのオブジェクトを派生させればいよい。
	 */
	class SyncObject : public ObjectLevelCountedLockable<SyncObject> {
		class WaitThreads : public ObjectLevelCountedLockable<WaitThreads> {
			Win32Event	waitSync_;						//	wait用同期
			::std::vector<Thread*>	waitThreads_;	//	wait中のthreadへのポインタ
		public:
			WaitThreads();
			virtual ~WaitThreads();
			void notify();
			void notifyAll();
			bool wait( SyncObject &monitorLock , int millisecond = INFINITE );
		};
		WaitThreads waitThreads_;
	public:
		SyncObject();
		virtual ~SyncObject();
		/**
		 * 一つの待機への通知。
		 * 待機スレッドのうち、どれか一つの待機を解除する。
		 */
		virtual void notify();
		/**
		 * すべての待機への通知。
		 * すべての待機を解除する。
		 */
		virtual void notifyAll();
		/**
		 * 待機
		 * 通知されるまで、待機する。
		 * wait中はLock(*this)オブジェクトによるロックは解除される。
		 */
		virtual void wait();
		/**
		 * 時間制限付き待機。
		 * 通知されるまで、待機する。ただしmillisecond[ms]で通知されなくても待機を抜ける。
		 * 待機中はlockによってロックされたロックは解除される。
		 * \param millisecond millisecond[ms]たって通知されなければ、待機を抜ける。
		 * \retval true 通知された。
		 * \retval false タイムアウトした。
		 */
		virtual bool wait( int millisecond );
		virtual ::std::string toString() const;
	protected:
		SyncObject( const SyncObject &syncObject );
		SyncObject &operator =( const SyncObject &syncObject );
	};
}
}

#endif //__SYNCOBJECT_H__