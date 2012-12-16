/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/Assert.cpp,v 1.7 2002/11/04 16:29:31 ama Exp $
 */

#include <cmath>


#include "Assert.h"
#include "NotEqualException.h"
#include "SourceLine.h"

namespace zefiro {
namespace std {


/// Check for a failed general assertion 
void 
Assert::assertImplementation( bool condition,
							 ::std::string conditionExpression,
                             long lineNumber,
							 ::std::string fileName )
{
  Asserter::failIf( condition, 
                    conditionExpression, 
					SourceLine( fileName, lineNumber ) );
}


/// Reports failed equality
void 
Assert::assertNotEqualImplementation( ::std::string expected,
									 ::std::string actual,
                                     long lineNumber,
									 ::std::string fileName )
{
  Asserter::failNotEqual( expected, 
                          actual, 
						  SourceLine( fileName, lineNumber ), "" );
}


/// Check for a failed equality assertion
void 
Assert::assertEquals( double expected, 
                          double actual, 
                          double delta,
                          long lineNumber,
						  ::std::string fileName )
{ 
  if (fabs (expected - actual) > delta) 
    assertNotEqualImplementation( assertion_traits<double>::toString(expected),
                                  assertion_traits<double>::toString(actual),
                                  lineNumber, 
                                  fileName ); 
}


void 
Assert::assertDoubleEquals( double expected,
                                double actual,
                                double delta,
                                SourceLine sourceLine )
{
  Asserter::failNotEqualIf( fabs( expected - actual ) > delta,
                            assertion_traits<double>::toString(expected),
                            assertion_traits<double>::toString(actual),
                            sourceLine );
}



}
}
