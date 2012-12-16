#pragma once
#include "std/COMObject.h"
#include "graphics/Color.h"
#include "graphics/Vertex.h"
#include <D3dx8tex.h>

namespace zefiro{
namespace graphics{
class GraphicsDevice;
class Texture{
public:
	Texture():rows_(NULL),count_(0){
	}
	virtual ~Texture(){
	}
	void create( int width , int height , Color color ,  IDirect3DTexture8* texture ){
		width_ = width;
		height_ = height;
		color_ = color;
		texture_.set(texture);
		if( rows_ == NULL ){
			rows_ = new BYTE*[height];
		}
		D3DSURFACE_DESC desc;
		HRESULT hr = texture_->GetLevelDesc( 0 , &desc );
		
		float heightRatio = (height + 0.5f )/ desc.Height;
		float widthRatio = (width + 0.5f ) / desc.Width;;
																cv_[0].rhw = 1.0f;
		cv_[1].x = (float)width;	cv_[1].y = (float)height;	cv_[1].rhw = 1.0f;	cv_[1].tu = widthRatio;	cv_[1].tv = heightRatio;
									cv_[2].y = (float)height;	cv_[2].rhw = 1.0f;							cv_[2].tv = heightRatio;
		cv_[3].x = (float)width;								cv_[3].rhw = 1.0f;	cv_[3].tu = widthRatio;
		cv_[4] = cv_[1];
																cv_[5].rhw = 1.0f;

	}
	void release(){
		if( rows_ != NULL ){
			delete[] rows_;
			rows_ = NULL;
		}
		if( count_ > 0 ){
			count_ = 1;
			unlock();
		}
	}
	void* getRow( int y )const{
		return rows_[y];
	}
	void** getRows()const{
		return (void**)rows_;
	}
	int getWidth() const{
		return width_;
	}
	int getHeight() const{
		return height_;
	}
	Color getColor() const{
		return color_;
	}
	void lock(){
		if( count_ == 0){
			D3DLOCKED_RECT rect;
			HRESULT hr = texture_->LockRect(1,&rect,NULL,D3DLOCK_NOSYSLOCK);
			if( hr != D3D_OK ){
				DXASSERT(hr);
			}
			for( int y=0 ; y<height_ ; ++y ){
				rows_[y] = (BYTE*)rect.pBits + rect.Pitch * y;
			}
		}
		++count_;
	}
	void unlock(){
		--count_;
		if( count_ == 0 ){
			texture_->UnlockRect(1);
		}
	}
	zefiro::std::COMObject<IDirect3DTexture8>& getTexture(){
		return texture_;
	}
	CUSTOMVERTEX& getVertex(const int i){
		return cv_[i];
	}
private:
	int count_;
	BYTE** rows_;
	int width_;
	int height_;
	Color color_;
	zefiro::std::COMObject<IDirect3DTexture8> texture_;
	CUSTOMVERTEX cv_[6];			
};
}
}