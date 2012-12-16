/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/Asserter.cpp,v 1.5 2002/11/14 16:52:32 ama Exp $
 */

#include "Asserter.h"
#include "NotEqualException.h"


namespace zefiro
{
namespace std
{

namespace Asserter
{

void 
fail( ::std::string message, 
      SourceLine sourceLine )
{
  throw Exception( message, sourceLine );
}


void 
failIf( bool shouldFail, 
	   ::std::string message, 
        SourceLine location )
{
  if ( shouldFail )
    fail( message, location );
}


void 
failNotEqual( ::std::string expected, 
			 ::std::string actual, 
              SourceLine sourceLine,
			  ::std::string additionalMessage )
{
  throw NotEqualException( expected, 
                           actual, 
                           additionalMessage ,
						   sourceLine)
                           ;
}


void 
failNotEqualIf( bool shouldFail,
			   ::std::string expected, 
			   ::std::string actual, 
                SourceLine sourceLine,
				::std::string additionalMessage )
{
  if ( shouldFail )
    failNotEqual( expected, actual, sourceLine, additionalMessage );
}


} // namespace Asserter
} // namespace std
} // namespace zefiro
