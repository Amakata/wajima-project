/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/sys/Win32Assert.cpp,v 1.5 2002/11/14 16:52:53 ama Exp $
 */

#include "Win32Assert.h"

#include <string>
#include <windows.h>

namespace zefiro {
namespace std {
	namespace Win32Assert {
		void Win32Assert( ::std::string message , DWORD result , ::zefiro::std::SourceLine sourceLine  ){
			switch( result ){
			case ERROR_SUCCESS:
				break;
			default:
				char *tcMessage;
				if( 0 == FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS |FORMAT_MESSAGE_FROM_SYSTEM , NULL , result , MAKELANGID(LANG_JAPANESE,  SUBLANG_ENGLISH_US),(LPTSTR)&tcMessage , 0 , NULL ) ){
					throw ::zefiro::std::Win32Exception( "" , GetLastError() , ZEFIRO_STD_SOURCELINE() );
				}
				throw ::zefiro::std::Win32Exception( ::std::string(tcMessage)+message , result , sourceLine );
			}
		}
	};
}
}