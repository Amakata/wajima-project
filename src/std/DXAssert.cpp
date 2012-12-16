#include "DXAssert.h"

#pragma comment(lib,"dxerr9.lib")
#include <string>
#include <windows.h>
#include <dxerr9.h>

namespace zefiro {
namespace std {
	namespace DXAssert {
		void DXAssert( ::std::string message , DWORD result , ::zefiro::std::SourceLine sourceLine  ){
			switch( result ){
			case ERROR_SUCCESS:
				break;
			default:
				::std::string name(DXGetErrorString9(result));
				::std::string description(DXGetErrorDescription9(result));
				throw ::zefiro::std::DXException( name+" "+description+" "+message , result , sourceLine );
			}
		}
	};
}
}