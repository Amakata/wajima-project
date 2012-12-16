/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/IllegalThreadStateException.cpp,v 1.5 2002/11/14 16:53:22 ama Exp $
 */

#include "IllegalThreadStateException.h"

namespace zefiro {
namespace system {
	IllegalThreadStateException::IllegalThreadStateException( ::std::string message , zefiro::std::SourceLine sourceLine ):Exception( message , sourceLine ){
	}
	IllegalThreadStateException::IllegalThreadStateException( ::std::string message , long lineNumber , ::std::string fileName )
		:Exception( message , lineNumber , fileName ){
	}
	IllegalThreadStateException::IllegalThreadStateException( const IllegalThreadStateException &other ):Exception( other){
	}
	IllegalThreadStateException::~IllegalThreadStateException(){
	}
	IllegalThreadStateException &IllegalThreadStateException::operator =( const IllegalThreadStateException &other ){
		Exception::operator =( other );
		return *this;
	}
	zefiro::std::Exception *IllegalThreadStateException::clone() const{
		return new IllegalThreadStateException( *this );
	}
	bool IllegalThreadStateException::isInstanceOf( const zefiro::std::Exception::Type &exceptionType  ) const{
	  return exceptionType == type()  ||
		Exception::isInstanceOf( exceptionType );
	}

	zefiro::std::Exception::Type IllegalThreadStateException::type(){
		return zefiro::std::Exception::Type( "zefiro::system::IllegalThreadStateException" );
	}
}
}