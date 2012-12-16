#pragma once

#include "std/COMObject.h"
#include "std/NullPointerException.h"
#include "std/DXAssert.h"
#include "loki/Singleton.h"
#include "system/ThreadingModel.h"
#include "application/ApplicationBase.h"
#include "graphics/Color.h"
#include "graphics/Depth.h"
#include "graphics/Pixel.h"
#include <ddraw.h>
#include <vector>

#pragma comment(lib,"ddraw.lib")


namespace zefiro{
namespace graphics{
class GraphicsSystem;
typedef Loki::SingletonHolder<GraphicsSystem,Loki::CreateUsingNew, Loki::DefaultLifetime,zefiro::system::ClassLevelCountedLockable> SingleGraphicsSystem;

class GraphicsSystem : zefiro::system::ClassLevelCountedLockable<GraphicsSystem> {
public:
	virtual ~GraphicsSystem(){
		release();
	}
	void create(){
		Lock(*this);
		if( dd7_.empty() ){
			LPDIRECTDRAW7 dd7;
			HRESULT hr = DirectDrawCreateEx(NULL  ,(LPVOID*)&dd7,IID_IDirectDraw7,NULL);
			if( hr != DD_OK ){
				DXASSERT(hr);
			}
			dd7_.set(dd7);
		}
		++count_;
	}
	void release(){
		Lock(*this);
		--count_;
		if( count_ == 0 && (!dd7_.empty()) ){
			dd7_.release();
		}
	}
	zefiro::std::COMObject<IDirectDraw7>& get(){
		return dd7_;
	}
private:
	friend Loki::CreateUsingNew<GraphicsSystem>;
	GraphicsSystem():count_(0){
	}
	int count_;
	zefiro::std::COMObject<IDirectDraw7> dd7_;
};


class GraphicsDevice{
public:
	GraphicsDevice():width_(0),height_(0),rows_(NULL),count_(0),isWindowed_(false){
		GraphicsSystem& gs = SingleGraphicsSystem::Instance();
		gs.create();
	}
	virtual ~GraphicsDevice(){
		release();
		GraphicsSystem& gs = SingleGraphicsSystem::Instance();
		gs.release();
	}
	void create( unsigned int adapter , unsigned int width , unsigned int height , Color color , Depth depth , bool windowed ){
		GraphicsSystem& gs = SingleGraphicsSystem::Instance();
		zefiro::application::ApplicationBase* ab = zefiro::application::ApplicationBase::getCurrentApplicationBase();
		// DDrawのモード設定
		{
			DWORD flags;
			if( windowed ){
				flags = DDSCL_NORMAL;
			}else{
				flags = DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT;
			}
			HRESULT hr = gs.get()->SetCooperativeLevel( ab->getWindow()->getHWnd() , flags );
			if( hr != DD_OK ){
				DXASSERT(hr);
			}
		}
		// クリッパ作成
		{
			LPDIRECTDRAWCLIPPER clip;
			HRESULT hr = gs.get()->CreateClipper(NULL,&clip,NULL);
			if( hr != DD_OK ){
				DXASSERT(hr);
			}
			clip_.set(clip);
		}
		// サーフェースの作成
		if( windowed ){
			// フロントサーフェースの作成
			{
				DDSURFACEDESC2 ddsd = {0};
				ddsd.dwSize = sizeof( ddsd );
				ddsd.dwFlags = DDSD_CAPS;
				ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
				LPDIRECTDRAWSURFACE7 frontSurface;
				HRESULT hr = gs.get()->CreateSurface(&ddsd,&frontSurface,NULL);
				if( hr != DD_OK ){
					DXASSERT(hr);
				}
				frontSurface_.set(frontSurface);
			}
			// バックサーフェースの作成
			{
				
				DDPIXELFORMAT ddpf;
				ddpf.dwSize = sizeof(ddpf);
				HRESULT hr = frontSurface_->GetPixelFormat(&ddpf);
				if( hr != DD_OK ){
					DXASSERT(hr);
				}
				DDSURFACEDESC2 ddsd = {0};
				ddsd.dwSize = sizeof( ddsd );
				ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
				ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
				ddsd.dwHeight = height;
				ddsd.dwWidth  = width;
				ddsd.ddpfPixelFormat = ddpf;
				LPDIRECTDRAWSURFACE7 backSurface;
				hr = gs.get()->CreateSurface(&ddsd,&backSurface,NULL);
				if( hr != DD_OK ){
					DXASSERT(hr);
				}
				backSurface_.set(backSurface);
				
			}
			// クリッパとウィンドウの関連付け
			{
				HRESULT hr = clip_->SetHWnd(0, ab->getWindow()->getHWnd() );
				if( hr != DD_OK ){
					DXASSERT(hr);
				}
			}
			// クリッパのセット
			{
				HRESULT hr = frontSurface_->SetClipper(clip_.get());
				if( hr != DD_OK ){
					DXASSERT(hr);
				}
			}
			// カラーの取得
			{
				DDPIXELFORMAT ddpf;
				ddpf.dwSize = sizeof(ddpf);
				HRESULT hr = backSurface_->GetPixelFormat(&ddpf);
				if( hr != DD_OK ){
					DXASSERT(hr);
				}
				switch( ddpf.dwRGBBitCount ){
				case 16:
					if(ddpf.dwRBitMask == 0xf800 && ddpf.dwGBitMask == 0x07e0 && ddpf.dwBBitMask == 0x001f) {
						color.setFormat(Color::R5G6B5);
					}else if(ddpf.dwRBitMask == 0x7c00 && ddpf.dwGBitMask == 0x03e0 && ddpf.dwBBitMask == 0x001f) {
						color.setFormat(Color::X1R5G5B5);
					}else{
						// TODO: えらー処理
					}
					break;
				case 24:
					if( ddpf.dwRBitMask == 0x00ff0000 ){
						color.setFormat(Color::R8G8B8);
					}else if( ddpf.dwRBitMask ==0x000000ff ){
						color.setFormat(Color::B8G8R8);
					}else{
						// TODO: えらー処理
					}
					break;
				case 32:
					if( ddpf.dwRBitMask == 0x00ff0000 ){
						color.setFormat(Color::X8R8G8B8);
					}else if( ddpf.dwRBitMask ==0x000000ff ){
						color.setFormat(Color::X8B8G8R8);
					}else{
						// TODO: えらー処理
					}
					break;
				default:
					// TODO: えらー処理
					break;
				}
			}
		}else{
			// TODO: フルスクリーンモードの実装
		}

		isWindowed_ = windowed;
		width_ = width;
		height_ = height;
		color_ = color;
		if( rows_ != NULL ){
			delete[] rows_;
		}
        rows_ = new BYTE*[height_];
	}
	void release(){
		if( count_ > 0 ){
			count_ = 1;
			unlock();
		}
		if( rows_ != NULL ){
			delete[] rows_;
		}
	}
	void clear(){
		DDBLTFX ddbltfx = {0};
		ddbltfx.dwSize = sizeof(ddbltfx);
		ddbltfx.dwFillColor = 0;
		HRESULT hr = backSurface_->Blt(NULL,NULL,NULL,DDBLT_COLORFILL, &ddbltfx);
		if( hr != DD_OK ){
			DXASSERT(hr);
		}
	}
	void present(){
		if( isWindowed_ ){
			zefiro::application::ApplicationBase* ab = zefiro::application::ApplicationBase::getCurrentApplicationBase();
			RECT rect;
			GetClientRect(ab->getWindow()->getHWnd(),&rect);
			ClientToScreen(ab->getWindow()->getHWnd(),(LPPOINT)&rect);
			ClientToScreen(ab->getWindow()->getHWnd(),(LPPOINT)&rect+1);
			HRESULT hr = frontSurface_->Blt(&rect,backSurface_.get(),NULL,DDBLT_WAIT,NULL);
			if( hr == DDERR_SURFACELOST ){
                reset();
			}else if( hr == DDERR_INVALIDRECT ){
                reset();
			}else if( hr != DD_OK ){
				DXASSERT(hr);
			}
		}else{
			// TODO: フルスクリーンモードの実装
		}
	}
	void reset(){
		GraphicsSystem& gs = SingleGraphicsSystem::Instance();
		HRESULT hr = gs.get()->RestoreAllSurfaces();
		if( hr != DD_OK ){
			DXASSERT(hr);
		}
	}
	void lock(){
		if( count_ == 0 ){
			DDSURFACEDESC2 ddsd={0};
			ddsd.dwSize = sizeof(ddsd);
			HRESULT hr = backSurface_->Lock(NULL,&ddsd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL );			
			if( hr != DD_OK ){
				DXASSERT(hr);
			}
			for( int row=0 ; row<height_ ; ++row ){
				rows_[row] =  (BYTE*)ddsd.lpSurface + ddsd.lPitch * row;
			}
		}
		++count_;
	}
	void unlock(){
		if( count_ > 0 ){
			--count_;
		}
		if( count_ == 0 ){
			HRESULT hr = backSurface_->Unlock(NULL);
			if( hr != DD_OK ){
				DXASSERT(hr);
			}
		}
	}
	void* getRow( int y )const{
		return rows_[y];
	}
	void** getRows()const{
		return (void**)rows_;
	}
	Color getColor()const{
		return color_;
	}
	int getWidth()const{
		return width_;
	}
	int getHeight()const{
		return height_;
	}
private:
	bool isWindowed_;
	int count_;
	int width_;
	int height_;
	Color color_;
	BYTE** rows_;
	zefiro::std::COMObject<IDirectDrawSurface7> frontSurface_;
	zefiro::std::COMObject<IDirectDrawSurface7> backSurface_;
	zefiro::std::COMObject<IDirectDrawClipper> clip_; 
};




}
}