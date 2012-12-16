#pragma once

namespace zefiro{
namespace graphics{

// サポートするピクセル
// X1R5G5B5 R5G6B5
// R8G8B8 B8G8R8
// X8R8G8B8 X8B8G8R8
// A8R8G8B8 A8B8G8R8

class X1R5G5B5Pixel{
public:
	void setR( BYTE r ){
		rgb_ = (rgb_ & 0x83ff) | ((WORD)(r & 0xf8) << 7);
	}
	void setG( BYTE g ){
		rgb_ = (rgb_ & 0xfc1f) | ((WORD)(g & 0xf8) << 2);
	}
	void setB( BYTE b ){
		rgb_ = (rgb_ & 0xffe0) | (b >> 3);
	}
	void setA( BYTE a ){
	}
	void setRGB(WORD rgb){
		rgb_ = rgb;
	}
	void setRGB( BYTE r , BYTE g  , BYTE b ){
		rgb_ = ((WORD)(r&0xf8) << 7) | ((WORD)(g&0xf8) << 2) | (b >> 3);
	}
	BYTE getR()const{
		return (rgb_ & 0x7c00) >> 7;
	}
	BYTE getG()const{
		return (rgb_ & 0x03e0) >> 2;
	}
	BYTE getB()const{
		return (rgb_ & 0x001f) << 3;
	}
	BYTE getA()const{
		return 255;
	}
	WORD getRGB()const{
		return rgb_;
	}
	template <class X>
	X1R5G5B5Pixel& operator = (const X &src){
		setRGB(src.getR(),src.getG(),src.getB());
		return *this;
	}
	X1R5G5B5Pixel& operator = (const X1R5G5B5Pixel &src){
		rgb_ = src.rgb_;
		return *this;
	}

private:
	WORD rgb_;
};



class R5G6B5Pixel{
public:
	void setR( BYTE r ){
		rgb_ = (rgb_ & 0x07ff) | ((WORD)(r & 0xf8) << 8);
	}
	void setG( BYTE g ){
		rgb_ = (rgb_ & 0xf81f) | ((WORD)(g & 0xfc) << 3);
	}
	void setB( BYTE b ){
		rgb_ = (rgb_ & 0xffe0) | (b >> 3);
	}
	void setA( BYTE a ){
	}
	void setRGB(WORD rgb){
		rgb_ = rgb;
	}
	void setRGB( BYTE r , BYTE g  , BYTE b ){
		rgb_ = ((WORD)(r&0xf8) << 8) | ((WORD)(g&0xfc) << 3) | (b >> 3);
	}
	BYTE getR()const{
		return (rgb_ & 0xf800) >> 8;
	}
	BYTE getG()const{
		return (rgb_ & 0x07e0) >> 3;
	}
	BYTE getB()const{
		return (rgb_ & 0x001f) << 3;
	}
	BYTE getA()const{
		return 255;
	}
	WORD getRGB()const{
		rgb_;
	}
	template <class X>
	R5G6B5Pixel& operator = (const X &src){
		setRGB(src.getR(),src.getG(),src.getB());
		return *this;
	}
	R5G6B5Pixel& operator = (const R5G6B5Pixel &src){
		rgb_ = src.rgb_;
		return *this;
	}

private:
	WORD rgb_;
};

class R8G8B8Pixel{
public:
	void setR( BYTE r ){
		r_ = r;
	}
	void setG( BYTE g ){
		g_ = g;
	}
	void setB( BYTE b ){
		b_ = b;
	}
	void setA( BYTE a ){
	}
	void setRGB(DWORD rgb){
		*(WORD*)(&b_) = (WORD)(rgb & 0xffff);
		*((BYTE*)(&b_)+2) = (BYTE)(rgb >> 16);		
	}
	void setRGB( BYTE r , BYTE g  , BYTE b ){
		r_ = r;
		g_ = g;
		b_ = b;
	}
	BYTE getR()const{
		return r_;
	}
	BYTE getG()const{
		return g_;
	}
	BYTE getB()const{
		return b_;
	}
	BYTE getA()const{
		return 255;
	}
	DWORD getRGB()const{
		return *(WORD*)(&b_) | (((DWORD)r_) << 16);
	}
	template <class X>
	R8G8B8Pixel& operator = (const X &src){
		setRGB(src.getR(),src.getG(),src.getB());
		return *this;
	}
	R8G8B8Pixel& operator = (const R8G8B8Pixel &src){
		*(WORD*)(&b_) = *(WORD*)(&src.b_);
		r_ = src.r_;
		return *this;
	}

private:
	BYTE b_,g_,r_;
};

class B8G8R8Pixel{
public:
	void setR( BYTE r ){
		r_ = r;
	}
	void setG( BYTE g ){
		g_ = g;
	}
	void setB( BYTE b ){
		b_ = b;
	}
	void setA( BYTE a ){
	}
	void setRGB(DWORD rgb){
		*(WORD*)(&r_) = (WORD)(rgb & 0xffff);
		*((BYTE*)(&r_)+2) = (BYTE)(rgb >> 16);		
	}
	void setRGB( BYTE r , BYTE g  , BYTE b ){
		r_ = r;
		g_ = g;
		b_ = b;
	}
	BYTE getR()const{
		return r_;
	}
	BYTE getG()const{
		return g_;
	}
	BYTE getB()const{
		return b_;
	}
	BYTE getA()const{
		return 255;
	}
	DWORD getRGB()const{
		return *(WORD*)(&r_) | (((DWORD)b_) << 16);
	}
	template <class X>
	B8G8R8Pixel& operator = (const X &src){
		setRGB(src.getR(),src.getG(),src.getB());
		return *this;
	}
	B8G8R8Pixel& operator = (const B8G8R8Pixel &src){
		*(WORD*)(&r_) = *(WORD*)(&src.r_);
		b_ = src.b_;
		return *this;
	}

private:
	BYTE r_,g_,b_;
};



class A8R8G8B8Pixel{
public:
	friend class X8R8G8B8Pixel;
	void setR( BYTE r ){
		r_ = r;
	}
	void setG( BYTE g ){
		g_ = g;
	}
	void setB( BYTE b ){
		b_ = b;
	}
	void setA( BYTE a ){
		a_ = a;
	}
	void setRGB(DWORD rgb){
		*(WORD*)(&b_) = (WORD)(rgb & 0xffff);
		*((BYTE*)(&b_)+2) = (BYTE)(rgb >> 16);		
	}
	void setRGB( BYTE r , BYTE g  , BYTE b ){
		r_ = r;
		g_ = g;
		b_ = b;
		a_ = 255;
	}
	void setRGBA( BYTE r , BYTE g , BYTE b , BYTE a ){
		r_ = r;
		g_ = g;
		b_ = b;
		a_ = a;
	}
	BYTE getR()const{
		return r_;
	}
	BYTE getG()const{
		return g_;
	}
	BYTE getB()const{
		return b_;
	}
	BYTE getA()const{
		return a_;
	}
	DWORD getRGB()const{
		return *(WORD*)(&b_) | (((DWORD)r_) << 16);
	}
	template <class X>
	A8R8G8B8Pixel& operator = (const X &src){
		setRGBA(src.getR(),src.getG(),src.getB(),src.getA());
		return *this;
	}
	A8R8G8B8Pixel& operator = (const A8R8G8B8Pixel &src){
		*(DWORD*)(&b_) = *(DWORD*)(&src.b_);
		return *this;		
	}

private:
	BYTE b_,g_,r_,a_;
};


class A8B8G8R8Pixel{
public:
	void setR( BYTE r ){
		r_ = r;
	}
	void setG( BYTE g ){
		g_ = g;
	}
	void setB( BYTE b ){
		b_ = b;
	}
	void setA( BYTE a ){
		a_ = a;
	}
	void setRGB(DWORD rgb){
		*(WORD*)(&r_) = (WORD)(rgb & 0xffff);
		*((BYTE*)(&r_)+2) = (BYTE)(rgb >> 16);		
	}
	void setRGB( BYTE r , BYTE g  , BYTE b ){
		r_ = r;
		g_ = g;
		b_ = b;
		a_ = 255;
	}
	void setRGBA( BYTE r , BYTE g , BYTE b , BYTE a ){
		r_ = r;
		g_ = g;
		b_ = b;
		a_ = a;
	}
	BYTE getR()const{
		return r_;
	}
	BYTE getG()const{
		return g_;
	}
	BYTE getB()const{
		return b_;
	}
	BYTE getA()const{
		return a_;
	}
	DWORD getRGB()const{
		return *(WORD*)(&r_) | (((DWORD)b_) << 16);
	}
	template <class X>
	A8B8G8R8Pixel& operator = (const X &src){
		setRGBA(src.getR(),src.getG(),src.getB(),src.getA());
		return *this;
	}
	A8B8G8R8Pixel& operator = (const A8B8G8R8Pixel &src){
		*(DWORD*)(&r_) = *(DWORD*)(&src.r_);
		return *this;		
	}

private:
	BYTE r_,g_,b_,a_;
};

class X8R8G8B8Pixel{
public:
	void setR( BYTE r ){
		r_ = r;
	}
	void setG( BYTE g ){
		g_ = g;
	}
	void setB( BYTE b ){
		b_ = b;
	}
	void setA( BYTE a ){
	}
	void setRGB(DWORD rgb){
		*(WORD*)(&b_) = (WORD)(rgb & 0xffff);
		*((BYTE*)(&b_)+2) = (BYTE)(rgb >> 16);		
	}
	void setRGB( BYTE r , BYTE g  , BYTE b ){
		r_ = r;
		g_ = g;
		b_ = b;
	}
	BYTE getR()const{
		return r_;
	}
	BYTE getG()const{
		return g_;
	}
	BYTE getB()const{
		return b_;
	}
	BYTE getA()const{
		return 255;
	}
	DWORD getRGB()const{
		return *(WORD*)(&b_) | (((DWORD)r_) << 16);
	}
	template <class X>
	X8R8G8B8Pixel& operator = (const X &src){
		setRGB(src.getR(),src.getG(),src.getB());
		return *this;
	}
	X8R8G8B8Pixel& operator = (const X8R8G8B8Pixel &src){
		*(DWORD*)(&b_) = *(DWORD*)(&src.b_);
		return *this;
	}
	X8R8G8B8Pixel& operator = (const A8R8G8B8Pixel &src){
		*(DWORD*)(&b_) = *(DWORD*)(&src.b_);
		return *this;
	}
private:
	BYTE b_,g_,r_,dummy_;
};


class X8B8G8R8Pixel{
public:
	void setR( BYTE r ){
		r_ = r;
	}
	void setG( BYTE g ){
		g_ = g;
	}
	void setB( BYTE b ){
		b_ = b;
	}
	void setA( BYTE a ){
	}
	void setRGB(DWORD rgb){
		*(WORD*)(&r_) = (WORD)(rgb & 0xffff);
		*((BYTE*)(&r_)+2) = (BYTE)(rgb >> 16);		
	}
	void setRGB( BYTE r , BYTE g  , BYTE b ){
		r_ = r;
		g_ = g;
		b_ = b;
	}
	BYTE getR()const{
		return r_;
	}
	BYTE getG()const{
		return g_;
	}
	BYTE getB()const{
		return b_;
	}
	BYTE getA()const{
		return 255;
	}
	DWORD getRGB()const{
		return *(WORD*)(&r_) | (((DWORD)b_) << 16);
	}
	template <class X>
	X8B8G8R8Pixel& operator = (const X &src){
		setRGB(src.getR(),src.getG(),src.getB());
		return *this;
	}
	X8B8G8R8Pixel& operator = (const X8B8G8R8Pixel &src){
		*(DWORD*)(&r_) = *(DWORD*)(&src.r_);
		return *this;
	}

private:
	BYTE r_,g_,b_,dummy_;
};
}
}