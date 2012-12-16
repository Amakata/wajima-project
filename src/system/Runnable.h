/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/Runnable.h,v 1.1 2002/11/03 09:05:26 ama Exp $
 */

#ifndef __RUNNABLE_H__
#define __RUNNABLE_H__

namespace zefiro {
namespace system {
	class Runnable
	{
	public:
		virtual void run()=0;
	};
}
}
#endif //__RUNNABLE_H__