/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/Mutex.h,v 1.1 2002/11/03 09:05:26 ama Exp $
 */

#ifndef __MUTEX_H__
#define __MUTEX_H__


#include <windows.h>
#include <string>

namespace zefiro {
namespace system {
	class Mutex
	{
	public:
		Mutex();
		virtual ~Mutex();
		void lock();
		void unlock();
		virtual ::std::string toString() const;
	private:
		CRITICAL_SECTION criticalSection_;
	};
}
}
#endif //__MUTEX_H__