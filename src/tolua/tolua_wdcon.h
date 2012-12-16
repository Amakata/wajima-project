#pragma once
#include "std/win32debug_console_stream.h"
// tolua_export
// tolua_begin
namespace zefiro{
	namespace tolua{
		class wdcon{
		public:
			wdcon(){
			}
			virtual ~wdcon(){
			}		
			void print( bool val ){
				::zefiro::std::win32debug_console_stream wd;
				wd << val;
			}
			void print( double val){
				::zefiro::std::win32debug_console_stream wd;
				wd << val;
			}
			void print ( char* str ){
				::zefiro::std::win32debug_console_stream wd;
				wd << str;
			}
		};
	}
}
// tolua_end
