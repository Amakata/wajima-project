/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/NotEqualException.h,v 1.3 2002/11/14 16:52:22 ama Exp $
 */

#ifndef NOTEQUALEXCEPTION_H
#define NOTEQUALEXCEPTION_H

#include "Exception.h"


namespace zefiro {
namespace std {

/*! \brief Exception thrown by failed equality assertions.
 * \ingroup BrowsingCollectedTestResult
 */
class NotEqualException : public Exception
{
public:
  /*! Constructs the exception.
   * \param expected Text that represents the expected value.
   * \param actual Text that represents the actual value.
   * \param sourceLine Location of the assertion.
   * \param additionalMessage Additionnal information provided to further qualify
   *                          the inequality.
   */
NotEqualException( ::std::string expected,
				  ::std::string actual, 
				  ::std::string additionalMessage = "" ,
                     SourceLine sourceLine = SourceLine()
                   );


NotEqualException( ::std::string expected,
				  ::std::string actual, 
                     long lineNumber, 
					 ::std::string fileName );


  NotEqualException( const NotEqualException &other );


  virtual ~NotEqualException() throw();

  ::std::string expectedValue() const;

  ::std::string actualValue() const;

  ::std::string additionalMessage() const;

  /*! Copy operator.
   * @param other Object to copy.
   * @return Reference on this object.
   */
  NotEqualException &operator =( const NotEqualException &other );

  Exception *clone() const;

  bool isInstanceOf( const Type &type ) const;

  static Type type();

private:
	::std::string m_expected;
	::std::string m_actual;
	::std::string m_additionalMessage;
};
}  // namespace std
}  // namespace zefiro

#endif  // NOTEQUALEXCEPTION_H
