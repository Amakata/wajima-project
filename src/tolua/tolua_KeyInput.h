#pragma once
#include "input/KeyInput.h"
// tolua_export
// tolua_begin
namespace zefiro{
	namespace tolua{
		class KeyInput{
		public:
			KeyInput(){
				input_.create();
			}
			virtual ~KeyInput(){
				input_.release();
			}
			bool getState(){
				return input_.getState();
			}
			bool isPress( int number )const{
				return input_.isPress(number);
			} 
		// tolua_end
		private:
			::zefiro::input::KeyInput input_;
		// tolua_begin
		};
	}
}
// tolua_end
