/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/std/Logger.h,v 1.3 2002/11/14 16:52:44 ama Exp $
 */

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <iostream>
#include <string>

#include "SourceLine.h"

namespace zefiro {
namespace std {
	class Logger
	{
	public:
		static void setOutputter( ::std::ostream *ostr );
		static void resetOutputter();
		static void logging( ::std::string kind , ::std::string message , SourceLine sourceLine  );
	private:
		static ::std::ostream *ostr__;
	};
}
}

#define ZEFIRO_LOG( kind , message ) ::zefiro::std::Logger::logging( kind , message , ZEFIRO_STD_SOURCELINE() )

#endif //__LOGGER_H__