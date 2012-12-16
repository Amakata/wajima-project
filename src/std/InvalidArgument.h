/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/InvalidArgument.h,v 1.3 2002/11/14 16:52:22 ama Exp $
 */
#ifndef __INVALIDARGUMENT_H__
#define __INVALIDARGUMENT_H__

#include "Exception.h"

namespace zefiro {
namespace std {
	class InvalidArgument : virtual public Exception
	{
	public:
		InvalidArgument( ::std::string message = "" , SourceLine sourceLine = SourceLine() );
		InvalidArgument( ::std::string message , long lineNumber, ::std::string fileName );
		InvalidArgument( const InvalidArgument &other );
		virtual ~InvalidArgument() throw();
		::std::string additionalMessage() const;
		/** Copy operator.
		* @param other Object to copy.
		* @return Reference on this object.
		*/
		InvalidArgument &operator =( const InvalidArgument &other );
		Exception *clone() const;
		bool isInstanceOf( const Type &type ) const;
		static Type type();

	};
}
}


#endif //__INVALIDARGUMENT_H__