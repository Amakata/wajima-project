/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/TimeOutException.cpp,v 1.5 2002/11/14 16:53:01 ama Exp $
 */

#include "TimeOutException.h"

namespace zefiro {
namespace system {
	TimeOutException::TimeOutException( ::std::string message , zefiro::std::SourceLine sourceLine ):Exception( message , sourceLine ){
	}
	TimeOutException::TimeOutException( ::std::string message , long lineNumber , ::std::string fileName ):Exception( message , lineNumber , fileName ){
	}
	TimeOutException::TimeOutException( const TimeOutException &other ):Exception( other){
	}
	TimeOutException::~TimeOutException(){
	}
	TimeOutException &TimeOutException::operator =( const TimeOutException &other ){
		Exception::operator =( other );
		return *this;
	}
	zefiro::std::Exception *TimeOutException::clone() const{
		return new TimeOutException( *this );
	}
	bool TimeOutException::isInstanceOf( const zefiro::std::Exception::Type &exceptionType  ) const{
	  return exceptionType == type()  ||
		Exception::isInstanceOf( exceptionType );
	}

	zefiro::std::Exception::Type TimeOutException::type(){
		return zefiro::std::Exception::Type( "zefiro::system::TimeOutException" );
	}
}
}