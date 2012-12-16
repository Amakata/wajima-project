#pragma once
#include ""
// tolua_export
// tolua_begin
namespace zefiro{
	namespace tolua{
		void pumpMessage( bool peek ){
			::zefiro::window::Window::pumpMessage(peek);
		}
		bool isQuit(){
			::zefiro::application::ApplicationBase* ab = ::zefiro::application::ApplicationBase::getCurrentApplicationBase();
			return ab->isQuit();
		}
	}
}
// tolua_end
