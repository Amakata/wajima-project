#pragma once


#include "Exception.h"
#include <windows.h>

namespace zefiro {
namespace std {
	class DXException : public Exception 
	{
	public:
		DXException( ::std::string message , DWORD errorCode , zefiro::std::SourceLine sourceLine = zefiro::std::SourceLine()  );
		DXException( ::std::string message , DWORD errorCode , long lineNumber, ::std::string fileName);
		DXException( const DXException &other );
		virtual ~DXException() throw();
		DWORD getError() const;
		DXException &operator =( const DXException &other );
		::zefiro::std::Exception *clone() const;
		bool isInstanceOf( const Type &type ) const;
		static Type type();
	protected:
		DWORD _errorCode;
	};
}
}