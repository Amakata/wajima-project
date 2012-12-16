/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/Assert.h,v 1.2 2002/11/04 16:29:31 ama Exp $
 */

#ifndef ZEFIRO_STD_ASSERT_H
#define ZEFIRO_STD_ASSERT_H

#include <sstream>

#include "Exception.h"
#include "NotEqualException.h"
#include "Asserter.h"

namespace zefiro {
namespace std {

  /*! \brief Traits used by ZEFIRO_STD_ASSERT_EQUAL().
   *
   * Here is an example of specialization of that traits:
   *
   * \code
   * template<>
   * struct assertion_traits<std::string>   // specialization for the std::string type
   * {
   *   static bool equal( const std::string& x, const std::string& y )
   *   {
   *     return x == y;
   *   }
   * 
   *   static std::string toString( const std::string& x )
   *   {
   *     std::string text = '"' + x + '"';    // adds quote around the string to see whitespace
   *     OStringStream ost;
   *     ost << text;
   *     return ost.str();
   *   }
   * };
   * \endcode
   */
  template <class T>
  struct assertion_traits 
  {  
      static bool equal( const T& x, const T& y )
      {
          return x == y;
      }

	  static ::std::string toString( const T& x )
      {
		  ::std::ostringstream  oss;
          oss << x;
          return oss.str();
      }
  };


  namespace Assert
  {
    void assertImplementation( bool         condition, 
		::std::string  conditionExpression = "",
        long lineNumber = Exception::UNKNOWNLINENUMBER ,
		::std::string  fileName = Exception::UNKNOWNFILENAME);

	void assertNotEqualImplementation( ::std::string expected,
		::std::string actual,
        long lineNumber,
		::std::string fileName );
      

    template <class T>
    void assertEquals( const T& expected,
                       const T& actual,
                       long lineNumber,
					   ::std::string fileName )
    {
      if ( !assertion_traits<T>::equal(expected,actual) ) // lazy toString conversion...
      {
        assertNotEqualImplementation( assertion_traits<T>::toString(expected),
                                      assertion_traits<T>::toString(actual),
                                      lineNumber, 
                                      fileName );
      }
    }

    void assertEquals( double expected, 
                                   double actual, 
                                   double delta, 
                                   long lineNumber,
								   ::std::string fileName );


    template <class T>
    void assertEquals( const T& expected,
                       const T& actual,
                       SourceLine sourceLine,
					   const ::std::string &message ="" )
    {
      if ( !assertion_traits<T>::equal(expected,actual) ) // lazy toString conversion...
      {
        Asserter::failNotEqual( assertion_traits<T>::toString(expected),
                                assertion_traits<T>::toString(actual),
                                sourceLine,
                                message );
      }
    }

    void assertDoubleEquals( double expected,
                                         double actual,
                                         double delta,
                                         SourceLine sourceLine );

  }


/* A set of macros which allow us to get the line number
 * and file name at the point of an error.
 * Just goes to show that preprocessors do have some
 * redeeming qualities.
 */

/** Assertions that a condition is \c true.
 * \ingroup Assertions
 */
#define ZEFIRO_STD_ASSERT(condition)                          \
	( ::zefiro::std::Asserter::failIf( !(condition),             \
                                 (#condition),             \
                                 ZEFIRO_STD_SOURCELINE() ) )

/** Assertion with a user specified message.
 * \ingroup Assertions
 * \param message Message reported in diagnostic if \a condition evaluates
 *                to \c false.
 * \param condition If this condition evaluates to \c false then the
 *                  test failed.
 */
#define ZEFIRO_STD_ASSERT_MESSAGE(message,condition)          \
	( ::zefiro::std::Asserter::failIf( !(condition),             \
                                 (message),                \
                                 ZEFIRO_STD_SOURCELINE() ) )

/** Fails with the specified message.
 * \ingroup Assertions
 * \param message Message reported in diagnostic.
 */
#define ZEFIRO_STD_FAIL( message )                            \
	( ::zefiro::std::Asserter::fail( message,                    \
                               ZEFIRO_STD_SOURCELINE() ) )



/** Asserts that two values are equals.
 * \ingroup Assertions
 *
 * Equality and string representation can be defined with
 * an appropriate zefiro::std::assertion_traits class.
 *
 * A diagnostic is printed if actual and expected values disagree.
 *
 * Requirement for \a expected and \a actual parameters:
 * - They are exactly of the same type
 * - They are serializable into a std::strstream using operator <<.
 * - They can be compared using operator ==. 
 *
 * The last two requirements (serialization and comparison) can be
 * removed by specializing the zefiro::std::assertion_traits.
 */
#define ZEFIRO_STD_ASSERT_EQUAL(expected,actual)                     \
	( ::zefiro::std::Assert::assertEquals( (expected),              \
                                         (actual),                \
                                         ZEFIRO_STD_SOURCELINE() ) )

/** Asserts that two values are equals, provides additional messafe on failure.
 * \ingroup Assertions
 *
 * Equality and string representation can be defined with
 * an appropriate assertion_traits class.
 *
 * A diagnostic is printed if actual and expected values disagree.
 * The message is printed in addition to the expected and actual value
 * to provide additional information.
 *
 * Requirement for \a expected and \a actual parameters:
 * - They are exactly of the same type
 * - They are serializable into a std::strstream using operator <<.
 * - They can be compared using operator ==. 
 *
 * The last two requirements (serialization and comparison) can be
 * removed by specializing the zefiro::std::assertion_traits.
 */
#define ZEFIRO_STD_ASSERT_EQUAL_MESSAGE(message,expected,actual)     \
	( ::zefiro::std::Assert::assertEquals( (expected),              \
                                         (actual),                \
                                         ZEFIRO_STD_SOURCELINE(),    \
                                         (message) ) )


/*! \brief Macro for primitive value comparisons
 * \ingroup Assertions
 */
#define ZEFIRO_STD_ASSERT_DOUBLES_EQUAL(expected,actual,delta)       \
	( ::zefiro::std::Assert::assertDoubleEquals( (expected),        \
                                               (actual),          \
                                               (delta),           \
                                               ZEFIRO_STD_SOURCELINE() ) )


} // namespace std
} // namespace zefiro

#endif  // ZEFIRO_STD_ASSERT_H
