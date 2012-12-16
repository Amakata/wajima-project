/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/IllegalThreadStateException.h,v 1.2 2002/11/14 16:53:22 ama Exp $
 */

#ifndef __ILLEGALTHREADSTATEEXCEPTION_H__
#define __ILLEGALTHREADSTATEEXCEPTION_H__

#include "std/Exception.h"

namespace zefiro {
namespace system {
	class IllegalThreadStateException : public zefiro::std::Exception
	{
	public:
		IllegalThreadStateException( ::std::string message = ""  , zefiro::std::SourceLine sourceLine = zefiro::std::SourceLine()
                     );
		IllegalThreadStateException( ::std::string message , long lineNumber, ::std::string fileName );
		IllegalThreadStateException( const IllegalThreadStateException &other );
		virtual ~IllegalThreadStateException();
		::std::string additionalMessage() const;
		/** Copy operator.
		* @param other Object to copy.
		* @return Reference on this object.
		*/
		IllegalThreadStateException &operator =( const IllegalThreadStateException &other );
		zefiro::std::Exception *clone() const;
		bool isInstanceOf( const zefiro::std::Exception::Type &type ) const;
		static zefiro::std::Exception::Type type();

	};
}
}


#endif //__ILLEGALTHREADSTATEEXCEPTION_H__