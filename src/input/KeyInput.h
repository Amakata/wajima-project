#pragma once
#ifndef DIRECTINPUT_VERSION
#define  DIRECTINPUT_VERSION 0x0700
#endif
#include "system/Thread.h"
#include "std/COMObject.h"
#include "std/DXAssert.h"
#include "std/NullPointerException.h"
#include "std/InvalidArgument.h"
#include "application/ApplicationInitializer.h"
#include "application/ApplicationBase.h"
#include <dinput.h>

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput.lib")

// tolua_export
// tolua_begin
namespace zefiro {
namespace input {
class KeyInput{
public:
	KeyInput():isAcquire_(false){
		::ZeroMemory(buffer_,sizeof(buffer_));
	}
	virtual ~KeyInput(){
		release();
	}
	// throw  DXException
	void create(){
		{
			input_.create(CLSID_DirectInput,IID_IDirectInput7);
			HRESULT hr = input_->Initialize( zefiro::application::ApplicationInitializer::getGHInstance() , DIRECTINPUT_VERSION );

			if( DI_OK != hr ){
				DXASSERT(hr);			
			}
		}
		{
			LPDIRECTINPUTDEVICE7 result;
			HRESULT hr = input_->CreateDeviceEx(GUID_SysKeyboard ,IID_IDirectInputDevice7,(LPVOID*)&result,NULL);
			if( hr != DI_OK ){
				DXASSERT(hr);
			}
			device_.set(result);
		}
		{
			HRESULT hr = device_->SetDataFormat(&c_dfDIKeyboard);
			if( hr != DI_OK ){
				DXASSERT(hr);
			}
		}
		{
			zefiro::application::ApplicationBase* ab = zefiro::application::ApplicationBase::getCurrentApplicationBase();
			// 協調レベルを設定する。
			HRESULT hr = device_->SetCooperativeLevel(ab->getWindow()->getHWnd(),DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
			if( hr != DI_OK ){
				DXASSERT(hr);
			}
		}
	}
	virtual void release(){
		::ZeroMemory(buffer_,sizeof(buffer_));
		if( !device_.empty() ){
			if( isAcquire_ ){
				device_->Unacquire();
			}
			device_.release();
		}
		isAcquire_ = false;
		if( !input_.empty() ){
			input_.release();
		}
	}
	// throw NullPointerException DXException
	bool getState(){
		if( device_.empty() ){
			throw zefiro::std::NullPointerException();
		}
		// 前回、デバイスを取得できなかった場合
		if( !isAcquire_ ){
			// デバイス取得
			HRESULT hr = device_->Acquire();
			if( hr == DI_OK || hr == S_FALSE ){			// 成功
				isAcquire_ = true;
			}else{										// 失敗
				::ZeroMemory(buffer_,sizeof(buffer_));
				isAcquire_ = false;	
				return false;
			}
		}
		{
			// デバイスの状態取得
			HRESULT hr = device_->GetDeviceState(sizeof(buffer_),(LPVOID)&buffer_);
			if( hr == DI_OK ){
				return true;	
			}else if( hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED ){ // デバイスを取得する必要がある。
				// デバイス取得
				HRESULT hr = device_->Acquire();
				if( hr == DI_OK || hr == S_FALSE){
					isAcquire_ = true;
				}else{
					::ZeroMemory(buffer_,sizeof(buffer_));
					isAcquire_ = false;	
					return false;
				}
				hr = device_->GetDeviceState(sizeof(buffer_),(LPVOID)&buffer_);
				if( hr == DI_OK ){
					return true;
				}else if( hr ==  DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED ){
					::ZeroMemory(buffer_,sizeof(buffer_));
					isAcquire_ =false;
					return false;
				}
			}else{
				::ZeroMemory(buffer_,sizeof(buffer_));
				isAcquire_ = false;
				DXASSERT(hr);
			}
		}
					
	}
	// throw InvalidArgument DXException
	bool isPress( int number )const{
		if( 0 <= number && number < sizeof(buffer_) ){
			return (buffer_[number] & 0x80) != 0;
		}else{
			throw zefiro::std::InvalidArgument();
		}
	}
private:
	bool isAcquire_;
	char buffer_[256];
	zefiro::std::COMObject<IDirectInput7> input_;
	zefiro::std::COMObject<IDirectInputDevice7> device_;
};
}
}
// tolua_end
