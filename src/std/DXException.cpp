#include "DXException.h"

namespace zefiro {
namespace std {
	DXException::DXException( ::std::string message , DWORD errorCode , ::zefiro::std::SourceLine sourceLine 
		):Exception(message,sourceLine),_errorCode(errorCode){
	}
	DXException::DXException(  ::std::string message , DWORD errorCode , long lineNumber, 
		::std::string fileName):Exception(message,lineNumber,fileName),_errorCode(errorCode){
	}
	DXException::DXException( const DXException &other ):Exception(other),_errorCode(other._errorCode){
	}
	DXException::~DXException() throw(){
	}
	DWORD DXException::getError() const{
		return _errorCode;
	}
	DXException &DXException::operator =( const DXException &other ){
		Exception::operator =( other );
		_errorCode = other._errorCode;
		return *this;
	}
	zefiro::std::Exception *DXException::clone() const{
		return new DXException( *this );
	}
	bool DXException::isInstanceOf( const Type& exceptionType ) const{
		return exceptionType == type();
	}
	Exception::Type DXException::type(){
		return Type( "zefiro::std::DXException" );
	}
}
}