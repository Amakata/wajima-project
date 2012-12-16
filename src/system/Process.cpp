/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/Process.cpp,v 1.3 2002/11/04 16:29:19 ama Exp $
 */

#include "Process.h"
#include "std/sys/Win32Assert.h"

namespace zefiro{
namespace system {
	Process::Process( ::std::string cmdLine ):_cmdLine(cmdLine),_process(NULL),_processID(0){
	}
	Process::~Process(){
	}
	void Process::start(){
		PROCESS_INFORMATION processInformation;
		STARTUPINFO	startupInfo;
		memset( &startupInfo , 0 , sizeof(startupInfo) );
		startupInfo.cb = sizeof(startupInfo);
		if( 0 == CreateProcess(NULL,const_cast<char*>(_cmdLine.c_str()),NULL,NULL,FALSE,0,NULL,NULL, &startupInfo , &processInformation ) ){
			WIN32ASSERT( GetLastError() );
		}
		_process = processInformation.hProcess;
		_processID = processInformation.dwProcessId;
	}
}
}