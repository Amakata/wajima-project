#pragma once
#include "graphics/Graphics7.h"
#include "graphics/Image.h"
#include "graphics/GraphicsConverter.h"
#include <vector>
#include <iostream>
#include <fstream>
// tolua_export
// tolua_begin
namespace zefiro{
	namespace tolua{
		class Graphics{
		public:
			Graphics(){
				device_ = new zefiro::graphics::GraphicsDevice();
//				font_ = new zefiro::graphics::Font(16,"ÇlÇr ÉSÉVÉbÉN",300);
			}
			virtual ~Graphics(){
			}
			void create( int width , int height ){
				device_->create(0,width,height,zefiro::graphics::Color(zefiro::graphics::Color::X8R8G8B8),zefiro::graphics::Depth(zefiro::graphics::Depth::D32),true);
			}
			void present(){
				device_->present();
			}
			void clear(){
				device_->clear();
			}
			void lock(){
				device_->lock();
			}
			void unlock(){
				device_->unlock();
			}
			int loadSprite( char* filename ){
				::std::ifstream ifs;
				ifs.open(filename,::std::ios_base::in|::std::ios_base::binary);
				zefiro::graphics::Sprite sprite(zefiro::graphics::ImageFactory::loadImage(ifs),0,0);
				ifs.close();
				sprites_.push_back(sprite);
				return sprites_.size()-1;
			}
			void clearSprite(){
				sprites_.clear();
			}
			void bltSinY( int num , int x , int y , int amp , int period ){
				sprites_[num].setX(x);
				sprites_[num].setY(y);
				zefiro::graphics::GraphicsConverter::blt(device_,sprites_[num],zefiro::graphics::CopySinY(),zefiro::graphics::CopySinYParam(amp,period));
			}
			void bltAlpha( int num , int x , int y ){
				sprites_[num].setX(x);
				sprites_[num].setY(y);
				zefiro::graphics::GraphicsConverter::blt(device_,sprites_[num],zefiro::graphics::AlphaAdd(),zefiro::graphics::AlphaAddParam());
			}
			void blt( int num , int x , int y ){
				sprites_[num].setX(x);
				sprites_[num].setY(y);
				zefiro::graphics::GraphicsConverter::blt(device_,sprites_[num],zefiro::graphics::Copy(),zefiro::graphics::CopyParam());
			}
			void bltText( char* str , int r , int g , int b , int x , int y ){
				Loki::SmartPtr<zefiro::graphics::Font> font(new zefiro::graphics::Font(16,"ÇlÇr ÉSÉVÉbÉN",300));
				zefiro::graphics::GraphicsConverter::blt(device_,zefiro::graphics::Text(),zefiro::graphics::TextParam(r,g,b,str,x,y,font,zefiro::graphics::TextParam::GRAY2));	
			}

		// tolua_end
		private:
//			Loki::SmartPtr<zefiro::graphics::Font> font_;
			Loki::SmartPtr<zefiro::graphics::GraphicsDevice> device_;
			::std::vector< zefiro::graphics::Sprite > sprites_;
			// tolua_begin
		};
	}
}
// tolua_end
