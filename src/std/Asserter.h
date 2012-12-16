/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/Asserter.h,v 1.2 2002/11/04 16:29:31 ama Exp $
 */

#ifndef ZEFIRO_STD_ASSERTER_H
#define ZEFIRO_STD_ASSERTER_H

#include <string>

#include "SourceLine.h"

namespace zefiro
{
namespace std
{

/*! \brief A set of functions to help writing assertion macros.
 * \ingroup CreatingNewAssertions
 *
 * \code
 * #include <std/SourceLine.h>
 * #include <std/Assert.h>
 * 
 * void 
 * checkXmlEqual( std::string expectedXml,
 *                std::string actualXml,
 *                zefiro::std::SourceLine sourceLine )
 * {
 *   std::string expected = XmlUniformiser( expectedXml ).stripped();
 *   std::string actual = XmlUniformiser( actualXml ).stripped();
 * 
 *   if ( expected == actual )
 *     return;
 * 
 *   ::zefiro::std::Asserter::failNotEqual( expected,
 *                                      actual,
 *                                      sourceLine );
 * }
 * 
 * \endcode
 */
namespace Asserter
{

  /*! Throws a Exception with the specified message and location.
   */
	void fail( ::std::string message, 
                         SourceLine sourceLine = SourceLine() );

  /*! Throws a Exception with the specified message and location.
   * \param shouldFail if \c true then the exception is thrown. Otherwise
   *                   nothing happen.
   * \param message Message explaining the assertion failiure.
   * \param sourceLine Location of the assertion.
   */
  void failIf( bool shouldFail, 
	  ::std::string message, 
      SourceLine sourceLine = SourceLine() );

  /*! Throws a NotEqualException with the specified message and location.
   * \param expected Text describing the expected value.
   * \param actual Text describing the actual value.
   * \param additionalMessage Additional message. Usually used to report
   *                          where the "difference" is located.
   * \param sourceLine Location of the assertion.
   */
  void failNotEqual( ::std::string expected, 
	  ::std::string actual, 
	  SourceLine sourceLine = SourceLine(),
	  ::std::string additionalMessage ="" );

  /*! Throws a NotEqualException with the specified message and location.
   * \param shouldFail if \c true then the exception is thrown. Otherwise
   *                   nothing happen.
   * \param expected Text describing the expected value.
   * \param actual Text describing the actual value.
   * \param additionalMessage Additional message. Usually used to report
   *                          where the "difference" is located.
   * \param sourceLine Location of the assertion.
   */
  void failNotEqualIf( bool shouldFail,
	  ::std::string expected, 
	  ::std::string actual, 
      SourceLine sourceLine = SourceLine(),
	  ::std::string additionalMessage ="" );

} // namespace Asserter
} // namespace std
} // namespace zefiro


#endif  // ZEFIRO_STD_ASSERTER_H
