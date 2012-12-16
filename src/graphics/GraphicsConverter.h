#pragma once

#include <windows.h>
#include "graphics/Color.h"
#include "graphics/Pixel.h"
#include "graphics/Sprite.h"
#include "graphics/Font.h"
#include <string>
#include <mbstring.h>
#include <math.h>
#include "std/win32debug_console_stream.h"

namespace zefiro{
namespace graphics{

// サポートするピクセル
// X1R5G5B5 R5G6B5
// R8G8B8 B8G8R8
// X8R8G8B8 X8B8G8R8
// A8R8G8B8 A8B8G8R8

class GraphicsConverter {
public:
	template <typename DST , typename FN , typename PARAM>
	static void blt( DST& dst , FN f ,  PARAM param ){
		RECT rect = {0,0,dst->getWidth(),dst->getHeight()};
		blt(dst,f,rect,param);
	}
	template <typename DST , typename FN , typename PARAM>
	static void blt( DST& dst , FN f , RECT rect , PARAM param ){
		dst->lock();
		switch( dst->getColor().getFormat() ){
			case Color::X8R8G8B8:
				FN::convert(X8R8G8B8Pixel(),dst,rect,param);
				break;
			case Color::X8B8G8R8:
				FN::convert(X8B8G8R8Pixel(),dst,rect,param);
				break;
			case Color::R8G8B8:
				FN::convert(R8G8B8Pixel(),dst,rect,param);
				break;
			case Color::B8G8R8:
				FN::convert(B8G8R8Pixel(),dst,rect,param);
				break;
			case Color::A8R8G8B8:
				FN::convert(A8R8G8B8Pixel(),dst,rect,param);
				break;
			case Color::A8B8G8R8:
				FN::convert(A8B8G8R8Pixel(),dst,rect,param);
				break;
			case Color::R5G6B5:
				FN::convert(R5G6B5Pixel(),dst,rect,param);
				break;
			case Color::X1R5G5B5:
				FN::convert(X1R5G5B5Pixel(),dst,rect,param);
				break;
		}
		dst->unlock();
	}

	template <typename DST , typename FN , typename PARAM>
	static void blt( DST& dst , Sprite& src , FN f , PARAM param ){
		RECT rect = {0,0,src.getImage()->getWidth(),src.getImage()->getHeight()};
		blt(dst,src.getImage(),f,src.getX(),src.getY(),rect,param);
	}
	template <typename DST , typename FN , typename PARAM>
	static void blt( DST& dst , Sprite& src , FN f , RECT srcRect , PARAM param ){
		blt(dst,src.getImage(),f,src.getX(),src.getY(),srcRect,param);
	}
	template <typename DST , typename SRC , typename FN , typename PARAM>
	static void blt( DST& dst , SRC& src , FN f , int x , int y , PARAM param ){
		RECT rect = {0,0,src->getWidth(),src->getHeight()};
		blt(dst,src,f,x,y,rect,param);
	}
	template <typename DST , typename SRC , typename FN , typename PARAM>
	static void blt( DST& dst , SRC& src , FN f , int x , int y , RECT srcRect , PARAM param ){
		dst->lock();
		src->lock();
		switch( dst->getColor().getFormat() ){
			case Color::X8R8G8B8:
				switch( src->getColor().getFormat() ){
					case Color::X8R8G8B8:
						FN::convert(X8R8G8B8Pixel(),X8R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::X8B8G8R8:
						FN::convert(X8R8G8B8Pixel(),X8B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::R8G8B8:
						FN::convert(X8R8G8B8Pixel(),R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::B8G8R8:
						FN::convert(X8R8G8B8Pixel(),B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::A8R8G8B8:
						FN::convert(X8R8G8B8Pixel(),A8R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::A8B8G8R8:
						FN::convert(X8R8G8B8Pixel(),A8B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::R5G6B5:
						FN::convert(X8R8G8B8Pixel(),R5G6B5Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::X1R5G5B5:
						FN::convert(X8R8G8B8Pixel(),X1R5G5B5Pixel(),dst,src,x,y,srcRect,param);
						break;
				}
				break;
			case Color::X8B8G8R8:
				switch( src->getColor().getFormat() ){
					case Color::X8R8G8B8:
						FN::convert(X8B8G8R8Pixel(),X8R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::X8B8G8R8:
						FN::convert(X8B8G8R8Pixel(),X8B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::R8G8B8:
						FN::convert(X8B8G8R8Pixel(),R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::B8G8R8:
						FN::convert(X8B8G8R8Pixel(),B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::A8R8G8B8:
						FN::convert(X8B8G8R8Pixel(),A8R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::A8B8G8R8:
						FN::convert(X8B8G8R8Pixel(),A8B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::R5G6B5:
						FN::convert(X8B8G8R8Pixel(),R5G6B5Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::X1R5G5B5:
						FN::convert(X8B8G8R8Pixel(),X1R5G5B5Pixel(),dst,src,x,y,srcRect,param);
						break;
				}
				break;
			case Color::R8G8B8:
				switch( src->getColor().getFormat() ){
					case Color::X8R8G8B8:
						FN::convert(R8G8B8Pixel(),X8R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::X8B8G8R8:
						FN::convert(R8G8B8Pixel(),X8B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::R8G8B8:
						FN::convert(R8G8B8Pixel(),R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::B8G8R8:
						FN::convert(R8G8B8Pixel(),B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::A8R8G8B8:
						FN::convert(R8G8B8Pixel(),A8R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::A8B8G8R8:
						FN::convert(R8G8B8Pixel(),A8B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::R5G6B5:
						FN::convert(R8G8B8Pixel(),R5G6B5Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::X1R5G5B5:
						FN::convert(R8G8B8Pixel(),X1R5G5B5Pixel(),dst,src,x,y,srcRect,param);
						break;
				}
				break;			
			case Color::B8G8R8:
				switch( src->getColor().getFormat() ){
					case Color::X8R8G8B8:
						FN::convert(B8G8R8Pixel(),X8R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::X8B8G8R8:
						FN::convert(B8G8R8Pixel(),X8B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::R8G8B8:
						FN::convert(B8G8R8Pixel(),R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::B8G8R8:
						FN::convert(B8G8R8Pixel(),B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::A8R8G8B8:
						FN::convert(B8G8R8Pixel(),A8R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::A8B8G8R8:
						FN::convert(B8G8R8Pixel(),A8B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::R5G6B5:
						FN::convert(B8G8R8Pixel(),R5G6B5Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::X1R5G5B5:
						FN::convert(B8G8R8Pixel(),X1R5G5B5Pixel(),dst,src,x,y,srcRect,param);
						break;
				}
				break;
			case Color::A8R8G8B8:
				switch( src->getColor().getFormat() ){
					case Color::X8R8G8B8:
						FN::convert(A8R8G8B8Pixel(),X8R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::X8B8G8R8:
						FN::convert(A8R8G8B8Pixel(),X8B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::R8G8B8:
						FN::convert(A8R8G8B8Pixel(),R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::B8G8R8:
						FN::convert(A8R8G8B8Pixel(),B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::A8R8G8B8:
						FN::convert(A8R8G8B8Pixel(),A8R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::A8B8G8R8:
						FN::convert(A8R8G8B8Pixel(),A8B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::R5G6B5:
						FN::convert(A8R8G8B8Pixel(),R5G6B5Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::X1R5G5B5:
						FN::convert(A8R8G8B8Pixel(),X1R5G5B5Pixel(),dst,src,x,y,srcRect,param);
						break;
				}
				break;
			case Color::A8B8G8R8:
				switch( src->getColor().getFormat() ){
					case Color::X8R8G8B8:
						FN::convert(A8B8G8R8Pixel(),X8R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::X8B8G8R8:
						FN::convert(A8B8G8R8Pixel(),X8B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::R8G8B8:
						FN::convert(A8B8G8R8Pixel(),R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::B8G8R8:
						FN::convert(A8B8G8R8Pixel(),B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::A8R8G8B8:
						FN::convert(A8B8G8R8Pixel(),A8R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::A8B8G8R8:
						FN::convert(A8B8G8R8Pixel(),A8B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::R5G6B5:
						FN::convert(A8B8G8R8Pixel(),R5G6B5Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::X1R5G5B5:
						FN::convert(A8B8G8R8Pixel(),X1R5G5B5Pixel(),dst,src,x,y,srcRect,param);
						break;
				}
				break;
			case Color::R5G6B5:
				switch( src->getColor().getFormat() ){
					case Color::X8R8G8B8:
						FN::convert(R5G6B5Pixel(),X8R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::X8B8G8R8:
						FN::convert(R5G6B5Pixel(),X8B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::R8G8B8:
						FN::convert(R5G6B5Pixel(),R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::B8G8R8:
						FN::convert(R5G6B5Pixel(),B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::A8R8G8B8:
						FN::convert(R5G6B5Pixel(),A8R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::A8B8G8R8:
						FN::convert(R5G6B5Pixel(),A8B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::R5G6B5:
						FN::convert(R5G6B5Pixel(),R5G6B5Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::X1R5G5B5:
						FN::convert(R5G6B5Pixel(),X1R5G5B5Pixel(),dst,src,x,y,srcRect,param);
						break;
				}
				break;
			case Color::X1R5G5B5:
				switch( src->getColor().getFormat() ){
					case Color::X8R8G8B8:
						FN::convert(X1R5G5B5Pixel(),X8R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::X8B8G8R8:
						FN::convert(X1R5G5B5Pixel(),X8B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::R8G8B8:
						FN::convert(X1R5G5B5Pixel(),R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::B8G8R8:
						FN::convert(X1R5G5B5Pixel(),B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::A8R8G8B8:
						FN::convert(X1R5G5B5Pixel(),A8R8G8B8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::A8B8G8R8:
						FN::convert(X1R5G5B5Pixel(),A8B8G8R8Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::R5G6B5:
						FN::convert(X1R5G5B5Pixel(),R5G6B5Pixel(),dst,src,x,y,srcRect,param);
						break;
					case Color::X1R5G5B5:
						FN::convert(X1R5G5B5Pixel(),X1R5G5B5Pixel(),dst,src,x,y,srcRect,param);
						break;
				}
				break;
			default:
				break;
		}
		src->unlock();
		dst->unlock();
	}
};


class CopyParam{
public:
	CopyParam(){
	}
};

class Copy{
public:
	// srcRectのチェックは外でやること
	template <typename DSTP , typename SRCP , typename DST , typename SRC , typename PARAM >
	static void convert( DSTP dstp , SRCP srcp , DST& dst , SRC& src  , int offsetX , int offsetY , RECT srcRect , PARAM param ){
		// srcRectがdstの範囲内かチェック
		if( offsetX + srcRect.left < 0 ){
			srcRect.left = -offsetX;
		}
		if( offsetY + srcRect.top < 0 ){
			srcRect.top = -offsetY;
		}
		if( offsetX + srcRect.right > dst->getWidth() ){
			srcRect.right = dst->getWidth() - offsetX;
		}
		if( offsetY + srcRect.bottom > dst->getHeight() ){
			srcRect.bottom = dst->getHeight() - offsetY;
		}
		// 描画すべきか判定
		if( srcRect.left >= srcRect.right ){
			return;
		}
		if( srcRect.top >= srcRect.bottom ){
			return;
		}
		for( int y = srcRect.top ; y<srcRect.bottom ; ++y ){
			DSTP* dstp = (DSTP*)dst->getRow(offsetY+y);
			SRCP* srcp = (SRCP*)src->getRow(y);
			for( int x = srcRect.left ; x<srcRect.right ; ++x ){
				dstp[offsetX+x] = srcp[x]; 
			}
		}
	}
};

class CopyExParam{
public:
	CopyExParam( BYTE alpha ):alpha_(alpha){
	}
	int getAlpha()const{
		return alpha_;
	}
private:
	BYTE alpha_;
};

class CopyEx{
public:
	// srcRectのチェックは外でやること
	template <typename DSTP , typename SRCP , typename DST , typename SRC , typename PARAM >
	static void convert( DSTP dstp , SRCP srcp , DST& dst , SRC& src  , int offsetX , int offsetY , RECT srcRect , PARAM param ){
		// srcRectがdstの範囲内かチェック
		if( offsetX + srcRect.left < 0 ){
			srcRect.left = -offsetX;
		}
		if( offsetY + srcRect.top < 0 ){
			srcRect.top = -offsetY;
		}
		if( offsetX + srcRect.right > dst->getWidth() ){
			srcRect.right = dst->getWidth() - offsetX;
		}
		if( offsetY + srcRect.bottom > dst->getHeight() ){
			srcRect.bottom = dst->getHeight() - offsetY;
		}
		// 描画すべきか判定
		if( srcRect.left >= srcRect.right ){
			return;
		}
		if( srcRect.top >= srcRect.bottom ){
			return;
		}
		for( int y = srcRect.top ; y<srcRect.bottom ; ++y ){
			DSTP* dstp = (DSTP*)dst->getRow(offsetY+y);
			SRCP* srcp = (SRCP*)src->getRow(y);
			for( int x = srcRect.left ; x<srcRect.right ; ++x ){
				if( param.getAlpha() < srcp[x].getA() ){ 
					dstp[offsetX+x] = srcp[x]; 
				}
			}
		}
	}
};



class AlphaAddParam{
public:
	AlphaAddParam(){
	}
};

class AlphaAdd{
public:
	// srcRectのチェックは外でやること
	template <typename DSTP , typename SRCP , typename DST , typename SRC , typename PARAM >
	static void convert( DSTP dstp , SRCP srcp , DST& dst , SRC& src  , int offsetX , int offsetY , RECT srcRect , PARAM param ){
		// テーブル(これくらいならキャッシュに入るっしょ)
		static int a[256] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,256};
		static int ia[256] = {256,254,253,252,251,250,249,248,247,246,245,244,243,242,241,240,239,238,237,236,235,234,233,232,231,230,229,228,227,226,225,224,223,222,221,220,219,218,217,216,215,214,213,212,211,210,209,208,207,206,205,204,203,202,201,200,199,198,197,196,195,194,193,192,191,190,189,188,187,186,185,184,183,182,181,180,179,178,177,176,175,174,173,172,171,170,169,168,167,166,165,164,163,162,161,160,159,158,157,156,155,154,153,152,151,150,149,148,147,146,145,144,143,142,141,140,139,138,137,136,135,134,133,132,131,130,129,128,127,126,125,124,123,122,121,120,119,118,117,116,115,114,113,112,111,110,109,108,107,106,105,104,103,102,101,100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,83,82,81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};

		// srcRectがdstの範囲内かチェック
		if( offsetX + srcRect.left < 0 ){
			srcRect.left = -offsetX;
		}
		if( offsetY + srcRect.top < 0 ){
			srcRect.top = -offsetY;
		}
		if( offsetX + srcRect.right > dst->getWidth() ){
			srcRect.right = dst->getWidth() - offsetX;
		}
		if( offsetY + srcRect.bottom > dst->getHeight() ){
			srcRect.bottom = dst->getHeight() - offsetY;
		}
		// 描画すべきか判定
		if( srcRect.left >= srcRect.right ){
			return;
		}
		if( srcRect.top >= srcRect.bottom ){
			return;
		}
		for( int y = srcRect.top ; y<srcRect.bottom ; ++y ){
			DSTP* out = (DSTP*)dst->getRow(offsetY+y) + offsetX + srcRect.left;
			SRCP* end = (SRCP*)src->getRow(y) + srcRect.right;
			for( SRCP* in = (SRCP*)src->getRow(y) + srcRect.left; in<end ; ++in , ++out ){
				out->setRGB( 
					(out->getR() * ia[in->getA()] + in->getR() * a[in->getA()])>>8 ,
					(out->getG() * ia[in->getA()] + in->getG() * a[in->getA()])>>8 ,
					(out->getB() * ia[in->getA()] + in->getB() * a[in->getA()])>>8 					
					);
			}
		}
	}
};




class CopySinYParam{
public:
	CopySinYParam(int amp,int period):amp_(amp),period_(period){
	}
	// Sinの振幅
	int getAmplitude()const{
		return amp_;
	}
	// 1ラジアンを何ドットにするか。
	int getPeriod()const{
		return period_;
	}
private:
	int amp_;
	int period_;
};

class CopySinY{
public:
	// srcRectのチェックは外でやること
	template <typename DSTP , typename SRCP , typename DST , typename SRC , typename PARAM >
	static void convert( DSTP dstp , SRCP srcp , DST& dst , SRC& src  , int offsetX , int offsetY , RECT srcRect , PARAM param ){
		int startx,endx,xPos;
		for( int y = srcRect.top ; y<srcRect.bottom ; ++y ){
			if( offsetY + y >= 0 && offsetY + y< dst->getHeight() ){
				xPos = (int)(param.getAmplitude()*sin(y*3.14159*2/param.getPeriod()));
				if( offsetX + srcRect.left + xPos >= 0 ){
					startx = srcRect.left;
				}else{
					startx = -(offsetX + xPos);
				}
				if( offsetX + srcRect.right + xPos < dst->getWidth() ){
					endx = srcRect.right;
				}else{
					endx = dst->getWidth()-(offsetX + xPos);
				}
				DSTP* dstp = (DSTP*)dst->getRow(offsetY+y)+offsetX+xPos+startx;
				SRCP* end = (SRCP*)src->getRow(y) + endx;
				for( SRCP* srcp = (SRCP*)src->getRow(y) + startx  ; srcp<end ; ++srcp , ++dstp ){
					*dstp = *srcp; 
				}
			}
		}
	}
};


class ClearParam{
public:
	ClearParam( BYTE r , BYTE g , BYTE b ):r_(r),g_(g),b_(b){
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
private:
	BYTE r_,g_,b_;
};

class Clear{
public:
	template <typename DSTP , typename DST , typename PARAM >
	static void convert( DSTP dstp , DST& dst , RECT rect , PARAM param ){
		DSTP p;
		p.setRGB(param.getR(),param.getG(),param.getB());
		for( int y = rect.top ; y<rect.bottom ; ++y ){
			DSTP* end = (DSTP*)dst->getRow(y) + rect.right;
			for( DSTP* dstp = (DSTP*)dst->getRow(y) + rect.left ; dstp<end ; ++dstp ){
				*dstp = p;
			}
		}
	}
};


class TextParam{
public:
	enum Antialiasing {GRAY2,GRAY4,GRAY8};
	TextParam( BYTE r , BYTE g , BYTE b , ::std::string text , int x , int y ,  Loki::SmartPtr<zefiro::graphics::Font>  font , Antialiasing aa = GRAY2 ):r_(r),g_(g),b_(b),text_(text),x_(x),y_(y),font_(font),aa_(aa){
	}
	::std::string getText(){
		return text_;
	}
	Loki::SmartPtr<zefiro::graphics::Font> getFont()const{
		return font_;
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
	int getX()const{
		return x_;
	}
	int getY()const{
		return y_;
	}
	Antialiasing getAntialiasing()const{
		return aa_;
	}
private:
	Loki::SmartPtr<zefiro::graphics::Font>  font_;
	::std::string text_;
	BYTE r_,g_,b_;
	int x_;
	int y_;
	Antialiasing aa_;	
};


class Text{
public:
	template <typename DSTP , typename DST , typename PARAM >
	static void convert( DSTP dstp , DST& dst , RECT rect , PARAM param ){
		// テーブル(これくらいならキャッシュに入るっしょ)
		static short int a8[65] = {0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80,84,88,92,96,100,104,108,112,116,120,124,128,132,136,140,144,148,152,156,160,164,168,172,176,180,184,188,192,196,200,204,208,212,216,220,224,228,232,236,240,244,248,252,256};
		static short int a4[17] = {0,16,32,48,64,80,96,112,128,144,160,176,192,208,224,240,256};
		static short int a2[5] = {0,64,128,192,256};
		short int* a;

		::std::string text = param.getText();
		unsigned char* pText = (unsigned char*)text.c_str();
		UINT code;
		TEXTMETRIC tm; 
		HDC hdc = CreateCompatibleDC(NULL);
        //フォントをメモリＤＣに登録
		HFONT hOldFont = (HFONT)SelectObject(hdc,param.getFont()->getHFont());
		GetTextMetrics(hdc,&tm);

		GLYPHMETRICS GlyphMetrics;
		MAT2 mat2 = {{0,2},{0,0},{0,0},{0,1}};
		int offsetX = param.getX();
		int offsetY = param.getY();
		UINT format;
		switch( param.getAntialiasing() ){
		case TextParam::GRAY2:
			format = GGO_GRAY2_BITMAP;
			a = a2;
			break;
		case TextParam::GRAY4:
			format = GGO_GRAY4_BITMAP;
			a = a4;
			break;
		case TextParam::GRAY8:
			format = GGO_GRAY8_BITMAP;
			a = a8;
			break;
		}
		while((code = _mbsnextc(pText)) != 0){
			// 出力先をはみ出していたら終了
			if( offsetX >= dst->getWidth() ){
				break;
			}

			// バッファサイズ取得&GlyphMetricsの取得
			int size = GetGlyphOutline(hdc,code,format,&GlyphMetrics,0,NULL,&mat2);
			// バッファ再確保
			Buffer::getSBuffer()->create(size);
			// 文字描画
			GetGlyphOutline(hdc,code,format,&GlyphMetrics,Buffer::getSBuffer()->getSize(),(LPVOID)Buffer::getSBuffer()->getBuffer(),&mat2);
			RECT rect={0,0,GlyphMetrics.gmBlackBoxX,GlyphMetrics.gmBlackBoxY};
			if( offsetX + GlyphMetrics.gmptGlyphOrigin.x + rect.left < 0 ){
				rect.left = -offsetX-GlyphMetrics.gmptGlyphOrigin.x;
			}
			if( offsetY + rect.top + tm.tmAscent - GlyphMetrics.gmptGlyphOrigin.y < 0 ){
				rect.top = -offsetY - tm.tmAscent + GlyphMetrics.gmptGlyphOrigin.y;
			}
			if( offsetX + GlyphMetrics.gmptGlyphOrigin.x + rect.right > dst->getWidth() ){
				rect.right = dst->getWidth() - offsetX;
			}
			if( offsetY + rect.bottom  + tm.tmAscent - GlyphMetrics.gmptGlyphOrigin.y> dst->getHeight() ){
				rect.bottom = dst->getHeight() - offsetY  - tm.tmAscent + GlyphMetrics.gmptGlyphOrigin.y;
			}
			if( rect.left < rect.right && rect.top < rect.bottom){
				for( int y=rect.top ; y< rect.bottom ; ++y ){
					DSTP* out = (DSTP*)dst->getRow(y+offsetY+ tm.tmAscent - GlyphMetrics.gmptGlyphOrigin.y) + offsetX+GlyphMetrics.gmptGlyphOrigin.x + rect.left;		
					BYTE* end = Buffer::getSBuffer()->getBuffer()+((GlyphMetrics.gmBlackBoxX + 3) &0xFFFC)*y + rect.right;
					for( BYTE* in =Buffer::getSBuffer()->getBuffer()+((GlyphMetrics.gmBlackBoxX + 3) &0xFFFC)*y + rect.left ; in<end ; ++in , ++out ){
						out->setRGB( 
									out->getR() + (((param.getR() - out->getR())* a[*in])>>8),
									out->getG() + (((param.getG() - out->getG())* a[*in])>>8),
									out->getB() + (((param.getB() - out->getB())* a[*in])>>8)
								);
					}
				}
			}
			offsetX += GlyphMetrics.gmCellIncX;
			pText = _mbsinc(pText);
		}
        SelectObject(hdc,hOldFont);
		DeleteDC(hdc);
	}
private:
	class Buffer{
	public:
		Buffer():buffer_(NULL),size_(0){
		}
		virtual ~Buffer(){
			if( buffer_ != NULL ){
				delete[] buffer_;
				size_ = 0;
				buffer_ = NULL;
			}
		}
		void create( int size ){
			if( size_ < size ){
				if( buffer_ != NULL ){
					delete[] buffer_;
					buffer_ = NULL;
				}
				buffer_ = new BYTE[size*2];
				size_ = size*2;
			}
		}
		int getSize()const{
			return size_;
		}
		BYTE* getBuffer()const{
			return buffer_;
		}
		static Buffer* getSBuffer(){
			return &buffer__;
		}
	private:
		int size_;
		BYTE* buffer_;
		static Buffer buffer__;
	};
};



}
}