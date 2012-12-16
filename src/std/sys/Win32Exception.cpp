/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/sys/Win32Exception.cpp,v 1.5 2002/11/14 16:52:53 ama Exp $
 */

#include "Win32Exception.h"

namespace zefiro {
namespace std {
	Win32Exception::Win32Exception( ::std::string message , DWORD errorCode , ::zefiro::std::SourceLine sourceLine 
		):Exception(message,sourceLine),_errorCode(errorCode){
	}
	Win32Exception::Win32Exception(  ::std::string message , DWORD errorCode , long lineNumber, 
		::std::string fileName):Exception(message,lineNumber,fileName),_errorCode(errorCode){
	}
	Win32Exception::Win32Exception( const Win32Exception &other ):Exception(other),_errorCode(other._errorCode){
	}
	Win32Exception::~Win32Exception() throw(){
	}
	DWORD Win32Exception::getError() const{
		return _errorCode;
	}
	Win32Exception &Win32Exception::operator =( const Win32Exception &other ){
		Exception::operator =( other );
		_errorCode = other._errorCode;
		return *this;
	}
	zefiro::std::Exception *Win32Exception::clone() const{
		return new Win32Exception( *this );
	}
	bool Win32Exception::isInstanceOf( const Type &exceptionType ) const{
		return exceptionType == type();
	}
	Exception::Type Win32Exception::type(){
		return Type( "zefiro::std::Win32Exception" );
	}
}
}