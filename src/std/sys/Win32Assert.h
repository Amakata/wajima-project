#ifndef __WIN32ASSERT_H__
#define __WIN32ASSERT_H__

#include <windows.h>

#include "../SourceLine.h"
#include "Win32Exception.h"

#define WIN32ASSERT( RESULT ) ::zefiro::std::Win32Assert::Win32Assert( "" , RESULT , ZEFIRO_STD_SOURCELINE() );
#define WIN32ASSERT_MESSAGE( MESSAGE , RESULT ) ::zefiro::std::Win32Assert::Win32Assert( MESSAGE , RESULT , ZEFIRO_STD_SOURCELINE() );

namespace zefiro {
namespace std {
	namespace Win32Assert {
		void Win32Assert( ::std::string message , DWORD result , ::zefiro::std::SourceLine sourceLine  );
	};
}
}

#endif //__WIN32ASSERT_H__