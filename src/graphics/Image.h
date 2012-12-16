#pragma once

#include <iostream>

#include "libpng/png.h"
#include "std/Exception.h"
#include "loki/SmartPtr.h"
#include "graphics/Color.h"

#pragma comment(lib, "zlib.lib")
#pragma comment(lib, "libpng.lib")

// tolua_export
// tolua_begin
namespace zefiro{
namespace graphics{

class Image {
public:	
	Image():width_(0),height_(0),data_(NULL),rows_(NULL){
	}
	virtual ~Image(){
		release();
	}
	void create( int width , int height , Color color ){
		data_ = new BYTE[width*height*color.getBitDepth()/8];
		rows_ = new BYTE*[height];
		if( (int)(data_) % 4 != 0 ){
			throw ::zefiro::std::Exception();
		}
		if( (int)(rows_) % 4 != 0 ){
			throw ::zefiro::std::Exception();
		}

		for( int y=0 ; y<height ; ++y ){
			rows_[y] = data_+y*width*color.getBitDepth()/8;
		}
		width_ = width;
		height_ = height;
		color_ = color;
	}
	void release(){
		if( data_ != NULL ){
			delete[] data_;
			data_ = NULL;
		}
		if( rows_ != NULL ){
			delete[] rows_;
			rows_ = NULL;
		}
		width_ = 0;
		height_ = 0;
		color_ =  Color();
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
	}
	void unlock(){
	}
// tolua_end
private:
	BYTE* data_;
	BYTE** rows_;
	int width_;
	int height_;
	Color color_;
// tolua_begin
};



class PNGLoadException : public ::zefiro::std::Exception {
public:
	PNGLoadException( ::std::string message , zefiro::std::SourceLine sourceLine = zefiro::std::SourceLine() ): Exception(message,sourceLine){
	}
	PNGLoadException( ::std::string message , long lineNumber, ::std::string fileName ): Exception(message,lineNumber,fileName){
	}
	PNGLoadException( const PNGLoadException &other ) : Exception(other) {
	}
// tolua_end
	virtual ~PNGLoadException() throw(){
	}

// tolua_begin
#if 0
	virtual ~PNGLoadException(){
	}
#endif
// tolua_end
	PNGLoadException &operator =( const PNGLoadException &other ){
		Exception::operator =( other );
		return *this;
	}
	::zefiro::std::Exception *clone() const{
		return new PNGLoadException( *this );
	}
// tolua_begin

	bool isInstanceOf( const Type &exceptionType ) const{
		return exceptionType == type();
	}
	static Type type(){
		return Type( "zefiro::graphics::PNGLoadException" );
	}
};

class ImageFactory{
// tolua_end

	static void PNGRead(png_structp png_ptr,png_bytep data,png_size_t length){
		::std::istream* is=(::std::istream*)png_get_io_ptr(png_ptr);
		is->read((char*)data,length);
	}
	static void PNGError(png_structp png_ptr, png_const_charp error_msg){
		throw PNGLoadException(error_msg,__LINE__,__FILE__);
	}
	static void PNGWarning(png_structp png_ptr,png_const_charp warning_msg){
		throw PNGLoadException(warning_msg,__LINE__,__FILE__);
	}
// tolua_begin
public:
	static Loki::SmartPtr<Image> create( int width , int height , zefiro::graphics::Color color ){
		Loki::SmartPtr<Image> result = Loki::SmartPtr<Image>(new Image());
		result->create(width,height,color);
		return result;
	}
	static Loki::SmartPtr<Image> loadImage( ::std::istream &is ){
		png_structp png_ptr = ::png_create_read_struct(
			PNG_LIBPNG_VER_STRING,
			NULL,
			NULL,
			NULL);
		if( png_ptr == NULL ){
			throw PNGLoadException("初期化に失敗しました。",__LINE__,__FILE__);
		}
		png_infop info_ptr = ::png_create_info_struct(png_ptr);
		if( info_ptr == NULL ){
			::png_destroy_read_struct(&png_ptr,NULL,NULL);
			throw PNGLoadException("初期化に失敗しました。",__LINE__,__FILE__);
		}
		::png_set_read_fn(png_ptr,&is,PNGRead);
		::png_set_error_fn(png_ptr,NULL,PNGError,PNGWarning);

		png_uint_32 width,height;
		int bit_depth,color_type,interlace_type;
	    int compression_type,filter_type;
		::png_read_info(png_ptr,info_ptr);
		::png_get_IHDR(png_ptr,info_ptr,&width,&height,&bit_depth,&color_type,&interlace_type,&compression_type,&filter_type);
		Loki::SmartPtr<Image> image = Loki::SmartPtr<Image>(new Image());
		if( color_type == PNG_COLOR_TYPE_RGB && bit_depth == 8 ){
			image->create(width,height,Color(Color::R8G8B8));
		}else if( color_type == PNG_COLOR_TYPE_RGB_ALPHA && bit_depth == 8 ){
			image->create(width,height,Color(Color::A8R8G8B8));
		}else{
			throw PNGLoadException("読み込めない画像フォーマットです。",__LINE__,__FILE__);
		}
		::png_set_bgr(png_ptr);
		::png_read_image(png_ptr,(png_bytepp)image->getRows());
		::png_read_end(png_ptr,info_ptr);
		::png_destroy_read_struct(&png_ptr,&info_ptr,(png_infopp)NULL);		
		return image;
	}
};

}
}

// tolua_end
