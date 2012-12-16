/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/RuntimeError.cpp,v 1.1 2002/11/18 14:09:19 ama Exp $
 */

#include "RuntimeError.h"

namespace zefiro {
namespace std {
	RuntimeError::RuntimeError( ::std::string message , SourceLine sourceLine ):Exception( message , sourceLine ){
	}
	RuntimeError::RuntimeError( ::std::string message , long lineNumber , ::std::string fileName ):Exception( message , lineNumber , fileName ){
	}
	RuntimeError::RuntimeError( const RuntimeError &other ):Exception( other){
	}
	RuntimeError::~RuntimeError(){
	}
	RuntimeError &RuntimeError::operator =( const RuntimeError &other ){
		Exception::operator =( other );
		return *this;
	}
	Exception *RuntimeError::clone() const{
		return new RuntimeError( *this );
	}
	bool RuntimeError::isInstanceOf( const Type &exceptionType  ) const{
	  return exceptionType == type()  ||
		Exception::isInstanceOf( exceptionType );
	}

	Exception::Type RuntimeError::type(){
		return Type( "zefiro_std::RuntimeError" );
	}
}
}