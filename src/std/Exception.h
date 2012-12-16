/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/Exception.h,v 1.2 2002/11/04 16:29:31 ama Exp $
 */

#ifndef ZEFIRO_STD_EXCEPTION_H
#define ZEFIRO_STD_EXCEPTION_H

#include <exception>
#include <string>

#include "SourceLine.h"
// tolua_export
// tolua_begin
namespace zefiro {
namespace std {

/*! \brief Exceptions thrown by failed assertions.
 * \ingroup BrowsingCollectedTestResult
 *
 * Exception is an exception that serves
 * descriptive strings through its what() method
 */
	class Exception : public ::std::exception
{
public:

    class Type
    {
    public:
		Type( ::std::string type ) : m_type ( type ) {}

        bool operator ==( const Type &other ) const
        {
	    return m_type == other.m_type;
        }
// tolua_end
	private:
		const ::std::string m_type;
// tolua_begin
	};


	Exception( ::std::string  message = "", 
	       SourceLine sourceLine = SourceLine() );

	Exception( ::std::string  message, 
	       long lineNumber, 
		   ::std::string fileName );

    Exception (const Exception& other);

// tolua_end
    virtual ~Exception () throw();
// tolua_begin
#if 0
	virtual ~Exception ();
#endif
// tolua_end
    Exception& operator = (const Exception& other);
    const char *what() const throw ();
// tolua_begin
#if 0
    const char *what() const;
#endif

    SourceLine sourceLine() const;

    long lineNumber() const;
// tolua_end
	::std::string fileName() const;
// tolua_begin

	static const ::std::string UNKNOWNFILENAME;
    static const long UNKNOWNLINENUMBER;

    virtual Exception *clone() const;
    
    virtual bool isInstanceOf( const Type &type ) const;

    static Type type();
// tolua_end
private:
    // VC++ does not recognize call to parent class when prefixed
    // with a namespace. This is a workaround.
	typedef ::std::exception SuperClass;

	::std::string m_message;
    SourceLine m_sourceLine;
// tolua_begin
};

} // namespace std
} // namespace zefiro
// tolua_end
#endif // ZEFIRO_STD_EXCEPTION_H

