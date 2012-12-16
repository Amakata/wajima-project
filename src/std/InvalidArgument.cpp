/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/InvalidArgument.cpp,v 1.6 2002/11/14 16:52:22 ama Exp $
 */

#include "InvalidArgument.h"

namespace zefiro {
namespace std {
	InvalidArgument::InvalidArgument( ::std::string message , SourceLine sourceLine ):Exception( message , sourceLine ){
	}
	InvalidArgument::InvalidArgument( ::std::string message , long lineNumber , ::std::string fileName ):Exception( message , lineNumber , fileName ){
	}
	InvalidArgument::InvalidArgument( const InvalidArgument &other ):Exception( other){
	}
	InvalidArgument::~InvalidArgument(){
	}
	InvalidArgument &InvalidArgument::operator =( const InvalidArgument &other ){
		Exception::operator =( other );
		return *this;
	}
	Exception *InvalidArgument::clone() const{
		return new InvalidArgument( *this );
	}
	bool InvalidArgument::isInstanceOf( const Type &exceptionType  ) const{
	  return exceptionType == type()  ||
		Exception::isInstanceOf( exceptionType );
	}

	Exception::Type InvalidArgument::type(){
		return Type( "zefiro::std::InvalidArgument" );
	}
}
}