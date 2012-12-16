/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/Process.h,v 1.1 2002/11/03 09:05:26 ama Exp $
 */

#ifndef __PROCESS_H__
#define __PROCESS_H__

#include <string>
#include <windows.h>

namespace zefiro {
namespace system {
	class Process
	{
	public:
		Process( ::std::string cmdLine );
		virtual ~Process();
		void start();
	protected:
		::std::string _cmdLine;
		HANDLE _process;
		DWORD _processID;
	};
}
}

#endif //__PROCESS_H__