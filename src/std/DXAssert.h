#pragma once

#include <windows.h>

#include "SourceLine.h"
#include "DXException.h"

#define DXASSERT( RESULT ) ::zefiro::std::DXAssert::DXAssert( "" , RESULT , ZEFIRO_STD_SOURCELINE() );
#define DXASSERT_MESSAGE( MESSAGE , RESULT ) ::zefiro::std::DXAssert::DXAssert( MESSAGE , RESULT , ZEFIRO_STD_SOURCELINE() );

namespace zefiro {
namespace std {
	namespace DXAssert {
		void DXAssert( ::std::string message , DWORD result , ::zefiro::std::SourceLine sourceLine  );
	};
}
}
