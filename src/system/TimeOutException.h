/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/TimeOutException.h,v 1.2 2002/11/14 16:53:01 ama Exp $
 */

#ifndef __TIMEOUTEXCEPTION_H__
#define __TIMEOUTEXCEPTION_H__

#include "std/Exception.h"

namespace zefiro {
namespace system {
	class TimeOutException : public zefiro::std::Exception
	{
	public:
		TimeOutException ( ::std::string message = ""  , zefiro::std::SourceLine sourceLine = zefiro::std::SourceLine() );
		TimeOutException ( ::std::string message , long lineNumber, 
			::std::string fileName );
		TimeOutException ( const TimeOutException  &other );
		virtual ~TimeOutException ();
		::std::string additionalMessage() const;
		/** Copy operator.
		* @param other Object to copy.
		* @return Reference on this object.
		*/
		TimeOutException  &operator =( const TimeOutException  &other );
		zefiro::std::Exception *clone() const;
		bool isInstanceOf( const zefiro::std::Exception::Type &type ) const;
		static zefiro::std::Exception::Type type();

	};
}
}


#endif //__TIMEOUTEXCEPTION_H__