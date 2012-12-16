#pragma once

namespace zefiro{
namespace graphics{
class Color {
public:
	enum Format {R8G8B8,B8G8R8,A8R8G8B8,A8B8G8R8,X8R8G8B8,X8B8G8R8,R5G6B5,X1R5G5B5,UNKNOWN};
	Color():format_(UNKNOWN){
	}
	Color( enum Format f ):format_(f){
	}
	virtual ~Color(){
	}
	int getBitDepth() const{
		switch( format_ ){
			case A8R8G8B8:
			case X8R8G8B8:
			case A8B8G8R8:
			case X8B8G8R8:
				return 32;
			case R8G8B8:
			case B8G8R8:
				return 24;
			case R5G6B5:
			case X1R5G5B5:
				return 16;
			default:
				return 0;
		}
	}

	enum Format getFormat()const{
		return format_;
	}
	void setFormat( enum Format f ){
		format_ = f;
	}
private:
	enum Format format_;
};
}
}