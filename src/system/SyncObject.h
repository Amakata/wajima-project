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
	 *	�����I�u�W�F�N�g�B
	 *	�X���b�h�Ԃł̓������Ƃ邽�߂̃I�u�W�F�N�g�ł���B
	 *	������r�����s�������I�u�W�F�N�g�͂��̃I�u�W�F�N�g��h��������΂��悢�B
	 */
	class SyncObject : public ObjectLevelCountedLockable<SyncObject> {
		class WaitThreads : public ObjectLevelCountedLockable<WaitThreads> {
			Win32Event	waitSync_;						//	wait�p����
			::std::vector<Thread*>	waitThreads_;	//	wait����thread�ւ̃|�C���^
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
		 * ��̑ҋ@�ւ̒ʒm�B
		 * �ҋ@�X���b�h�̂����A�ǂꂩ��̑ҋ@����������B
		 */
		virtual void notify();
		/**
		 * ���ׂĂ̑ҋ@�ւ̒ʒm�B
		 * ���ׂĂ̑ҋ@����������B
		 */
		virtual void notifyAll();
		/**
		 * �ҋ@
		 * �ʒm�����܂ŁA�ҋ@����B
		 * wait����Lock(*this)�I�u�W�F�N�g�ɂ�郍�b�N�͉��������B
		 */
		virtual void wait();
		/**
		 * ���Ԑ����t���ҋ@�B
		 * �ʒm�����܂ŁA�ҋ@����B������millisecond[ms]�Œʒm����Ȃ��Ă��ҋ@�𔲂���B
		 * �ҋ@����lock�ɂ���ă��b�N���ꂽ���b�N�͉��������B
		 * \param millisecond millisecond[ms]�����Ēʒm����Ȃ���΁A�ҋ@�𔲂���B
		 * \retval true �ʒm���ꂽ�B
		 * \retval false �^�C���A�E�g�����B
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