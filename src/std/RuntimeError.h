/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/RuntimeError.h,v 1.1 2002/11/18 14:09:19 ama Exp $
 */

#ifndef __RUNTIMEERROR_H__
#define __RUNTIMEERROR_H__

#include "Exception.h"

namespace zefiro {
namespace std {
	class RuntimeError : virtual public Exception
	{
	public:
		RuntimeError( ::std::string message = "" , SourceLine sourceLine = SourceLine() );
		RuntimeError( ::std::string message , long lineNumber, ::std::string fileName );
		RuntimeError( const RuntimeError &other );
		virtual ~RuntimeError() throw();
		::std::string additionalMessage() const;
		/** Copy operator.
		* @param other Object to copy.
		* @return Reference on this object.
		*/
		RuntimeError &operator =( const RuntimeError &other );
		Exception *clone() const;
		bool isInstanceOf( const Type &type ) const;
		static Type type();

	};
}
}

#endif //__RUNTIMEERROR_H__