/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/NullPointerException.cpp,v 1.1 2002/11/18 14:09:19 ama Exp $
 */

#include "NullPointerException.h"

namespace zefiro {
namespace std {
	NullPointerException::NullPointerException( ::std::string message , SourceLine sourceLine ):Exception( message , sourceLine ){
	}
	NullPointerException::NullPointerException( ::std::string message , long lineNumber , ::std::string fileName ):Exception( message , lineNumber , fileName ){
	}
	NullPointerException::NullPointerException( const NullPointerException &other ):Exception( other){
	}
	NullPointerException::~NullPointerException(){
	}
	NullPointerException &NullPointerException::operator =( const NullPointerException &other ){
		Exception::operator =( other );
		return *this;
	}
	NullPointerException *NullPointerException::clone() const{
		return new NullPointerException( *this );
	}
	bool NullPointerException::isInstanceOf( const Type &exceptionType  ) const{
	  return exceptionType == type()  ||
		Exception::isInstanceOf( exceptionType );
	}

	Exception::Type NullPointerException::type(){
		return Type( "zefiro::std::NullPointerException" );
	}
}
}