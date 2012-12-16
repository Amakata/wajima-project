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
#include "graphics/Texture.h"
#include <D3d8.h>

#include <vector>

#pragma comment(lib,"D3d8.lib")
#pragma comment(lib,"D3dx8.lib")


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
		if( d3d8_.empty() ){
			LPDIRECT3D8 d3d8 = Direct3DCreate8(D3D_SDK_VERSION);
			if( d3d8 == NULL ){
				throw zefiro::std::NullPointerException();
			}
			d3d8_.set(d3d8);
		}
		++count_;
	}
	void release(){
		Lock(*this);
		--count_;
		if( count_ == 0 && (!d3d8_.empty()) ){
			d3d8_.release();
		}
	}
	zefiro::std::COMObject<IDirect3D8>& get(){
		return d3d8_;
	}
private:
	friend Loki::CreateUsingNew<GraphicsSystem>;
	GraphicsSystem():count_(0){
	}
	int count_;
	zefiro::std::COMObject<IDirect3D8> d3d8_;
};


class GraphicsDevice{
public:
	GraphicsDevice():width_(0),height_(0),rows_(NULL),count_(0){
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
		D3DPRESENT_PARAMETERS param={0};
		param.BackBufferWidth = width;
		param.BackBufferHeight = height;ieie
		if( windowed ){
			D3DDISPLAYMODE mode;
			HRESULT hr = gs.get()->GetAdapterDisplayMode(adapter,&mode);
			if( hr != D3D_OK ){
				DXASSERT(hr);
			}
			param.BackBufferFormat = mode.Format;
			switch( mode.Format ){
			case D3DFMT_R8G8B8:
				color.setFormat(Color::R8G8B8);
				break;
			case D3DFMT_X8R8G8B8:
				color.setFormat(Color::X8R8G8B8);
				break;
			case D3DFMT_R5G6B5:
				color.setFormat(Color::R5G6B5);
				break;
			case D3DFMT_X1R5G5B5:
				color.setFormat(Color::X1R5G5B5);
				break;
			default:
				color.setFormat(Color::UNKNOWN);
				break;
			}
		}else{
			switch(color.getFormat()){
			case Color::R8G8B8:
				param.BackBufferFormat = D3DFMT_R8G8B8;
				break;
			case Color::X8R8G8B8:
				param.BackBufferFormat = D3DFMT_X8R8G8B8;
				break;
			case Color::R5G6B5:
				param.BackBufferFormat = D3DFMT_R5G6B5;
				break;
			case Color::X1R5G5B5:
				param.BackBufferFormat = D3DFMT_X1R5G5B5;
				break;
			default:
				param.BackBufferFormat = D3DFMT_UNKNOWN;
			}
		}
		param.BackBufferCount = 1;
		param.Windowed = windowed;
		param.MultiSampleType = D3DMULTISAMPLE_NONE;
//		if( windowed ){
			param.SwapEffect = D3DSWAPEFFECT_COPY;
//		}else{
//			param.SwapEffect = D3DSWAPEFFECT_FLIP;
//		}
		zefiro::application::ApplicationBase* ab = zefiro::application::ApplicationBase::getCurrentApplicationBase();
		param.hDeviceWindow = ab->getWindow()->getHWnd();
		param.EnableAutoDepthStencil = FALSE;
/*
		switch( depth.getFormat() ){
		case Depth::D16:
			param.AutoDepthStencilFormat = D3DFMT_D16;
			break;
		case Depth::D32:
			param.AutoDepthStencilFormat = D3DFMT_D32;
			break;
		case Depth::D15S1:
			param.AutoDepthStencilFormat = D3DFMT_D15S1;
			break;
		case Depth::D24X8:
			param.AutoDepthStencilFormat = D3DFMT_D24X8;
			break;
		case Depth::D24S8:
			param.AutoDepthStencilFormat = D3DFMT_D24S8;
			break;
		case Depth::D24X4S4:
			param.AutoDepthStencilFormat = D3DFMT_D24X4S4;
			break;
		default:
			param.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
			break;
		}*/
		param.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
		if( windowed ){
			param.FullScreen_RefreshRateInHz = 0;
		}else{
			param.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		}
		{
			LPDIRECT3DDEVICE8 device;
			HRESULT hr = gs.get()->CreateDevice( adapter , D3DDEVTYPE_HAL , ab->getWindow()->getHWnd() , D3DCREATE_HARDWARE_VERTEXPROCESSING , &param , &device );
			if( hr != D3D_OK ){
				HRESULT hr = gs.get()->CreateDevice( adapter , D3DDEVTYPE_REF , ab->getWindow()->getHWnd() , D3DCREATE_HARDWARE_VERTEXPROCESSING , &param , &device );
				if( hr != D3D_OK ){
					DXASSERT(hr);
				}
			}
			device_.set(device);
		}
		{
			HRESULT hr = device_->GetDeviceCaps(&caps_);
			if( hr != D3D_OK ){
				DXASSERT(hr);
			}
		}
		width_ = width;
		height_ = height;
		color_ = color;
		param_ = param;
		if( rows_ != NULL ){
			delete[] rows_;
		}
        rows_ = new BYTE*[height_];
	}
	Loki::SmartPtr<Texture> createTexture(int width,int height,Color color){
		Loki::SmartPtr<Texture> result = Loki::SmartPtr<Texture>(new Texture());
		D3DFORMAT format;
		IDirect3DTexture8* texture;
		switch( color.getFormat() ){
			case Color::A8R8G8B8:
				format = D3DFMT_A8R8G8B8;
				break;
			case Color::R8G8B8:
				format = D3DFMT_R8G8B8;
				break;
			case Color::R5G6B5:
				format = D3DFMT_R5G6B5;
				break;
			case Color::X1R5G5B5:
				format = D3DFMT_X1R5G5B5;
				break;
			case Color::X8R8G8B8:
				format = D3DFMT_X8R8G8B8;
				break;
			default:
				// TODO: ‚¦‚ç[ˆ—
				break;
		}
		HRESULT hr = device_->CreateTexture(width,height,1,NULL,format,D3DPOOL_MANAGED,&texture);
		if( hr != D3D_OK ){
			DXASSERT(hr);
		}
		result->create(width,height,color,texture);
		return result;
	}
	void release(){
		if( count_ > 0 ){
			count_ = 1;
			unlock();
		}
		if( rows_ != NULL ){
			delete[] rows_;
		}
		GraphicsSystem& gs = SingleGraphicsSystem::Instance();
		device_.release();
	}
	void present(){
		HRESULT hr = device_->Present(NULL,NULL,NULL,NULL);
		if( hr != D3D_OK ){
			if( hr == D3DERR_DEVICELOST ){
				reset();
			}else{
				DXASSERT(hr);
			}
		}
	}
	void reset(){
		surface_.release();
		HRESULT hr = device_->Reset(&param_);
		if( hr != D3D_OK ){
			if( hr != D3DERR_DEVICELOST ){
				DXASSERT(hr);
			}
		}

	}
	void lock(){
		if( count_ == 0 ){
			if( surface_.empty() ){
				IDirect3DSurface8* surface;
				HRESULT hr = device_->GetBackBuffer(0,D3DBACKBUFFER_TYPE_MONO,&surface);
				if( hr != D3D_OK ){
					DXASSERT(hr);
				}
				surface_.set(surface);
			}
			D3DLOCKED_RECT rect;
			surface_->LockRect(&rect,NULL,D3DLOCK_NOSYSLOCK );
			for( int row=0 ; row<height_ ; ++row ){
				rows_[row] =  (BYTE*)rect.pBits + rect.Pitch * row;
			}
		}
		++count_;
	}
	void unlock(){
		if( count_ > 0 ){
			--count_;
		}
		if( count_ == 0 ){
			surface_->UnlockRect();
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
	int count_;
	int width_;
	int height_;
	Color color_;
	BYTE** rows_;
	D3DPRESENT_PARAMETERS param_;
	zefiro::std::COMObject<IDirect3DSurface8> surface_;
	D3DCAPS8 caps_;
	zefiro::std::COMObject<IDirect3DDevice8> device_; 
};




}
}