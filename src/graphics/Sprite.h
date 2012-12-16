#pragma once

#include "loki/SmartPtr.h"
#include "graphics/Image.h"


namespace zefiro{
namespace graphics{
class Sprite{
public:
	Sprite( Loki::SmartPtr<zefiro::graphics::Image> image , int x , int y )
		:image_(image) , x_(x) , y_(y) {
	}
	void setX(int x){
		x_ = x;
	}
	void setY(int y){
		y_ = y;
	}
	int getX()const{
		return x_;
	}
	int getY()const{
		return y_;
	}
	Loki::SmartPtr<zefiro::graphics::Image> getImage()const{
		return image_;
	}
private:
	int x_;
	int y_;
	Loki::SmartPtr<zefiro::graphics::Image> image_;
};
}
}