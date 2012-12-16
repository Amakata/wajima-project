/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/Logger.cpp,v 1.3 2002/11/14 16:52:44 ama Exp $
 */

#include "Logger.h"

#include <fstream>

namespace zefiro {
namespace std {
	void Logger::setOutputter( ::std::ostream *ostr ){
		ostr__ = ostr;
	}
	void Logger::resetOutputter(){
		ostr__ = NULL;
	}
	void Logger::logging( ::std::string kind , ::std::string message , SourceLine sourceLine ){
		if( ostr__ == NULL ){
			return;
		}
		*ostr__ <<  sourceLine.fileName() << "(" << sourceLine.lineNumber() << ") : " << kind << " : " << message << ::std::endl;
		ostr__->flush();
	}
	::std::ostream* Logger::ostr__ = NULL;
}
}