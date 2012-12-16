/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/NullPointerException.h,v 1.1 2002/11/18 14:09:19 ama Exp $
 */
#ifndef __NULLPOINTEREXCEPTION_H__
#define __NULLPOINTEREXCEPTION_H__

#include "Exception.h"

namespace zefiro {
namespace std {
	class NullPointerException : public Exception {
	public:
		NullPointerException( ::std::string  message = "", SourceLine sourceLine = SourceLine() );
		NullPointerException( ::std::string  message, long lineNumber, ::std::string fileName );
	    NullPointerException (const NullPointerException& other);
	    virtual ~NullPointerException () throw();
		::std::string additionalMessage() const;
		/** Copy operator.
		* @param other Object to copy.
		* @return Reference on this object.
		*/
		NullPointerException &operator =( const NullPointerException &other );
		NullPointerException *clone() const;
		bool isInstanceOf( const Type &type ) const;
		static Type type();
	};
}
}

#endif //__NULLPOINTEREXCEPTION_H__