#pragma once
namespace zefiro{
namespace graphics{
class Depth {
public:
	enum Format {D16,D32,D15S1,D24X8,D24S8,D24X4S4,UNKNOWN};
	Depth():format_(UNKNOWN){
	}
	Depth( enum Format f ):format_(f){
	}
	virtual ~Depth(){
	}
	int getBitDepth() const{
		switch( format_ ){
			case D32:
			case D24X8:
			case D24X4S4:
				return 32;
			case D16:
			case D15S1:
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