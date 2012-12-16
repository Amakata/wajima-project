#pragma once
#include "input/MouseInput.h"
// tolua_export
// tolua_begin
namespace zefiro{
	namespace tolua{
		class MouseInput{
		public:
			MouseInput(){
				input_.create();
			}
			virtual ~MouseInput(){
				input_.release();
			}
			bool getState(){
				return input_.getState();
			}
			bool isPress( int number )const{
				return input_.isPress(number);
			}
			int getX()const{
				return input_.getX();
			}
			int getY()const{
				return input_.getY();
			}
			int getDiffX()const{
				return input_.getDiffX();
			}
			int getDiffY()const{
				return input_.getDiffY();
			}
		// tolua_end
		private:
			::zefiro::input::MouseInput input_;
		// tolua_begin
		};
	}
}
// tolua_end
