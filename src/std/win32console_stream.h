#pragma once

#include <iostream>
#include <ios>
#include "loki/Singleton.h"

namespace zefiro {
namespace std {

template <class Ch,class Tr=::std::char_traits<Ch> >
class basic_win32console_streambuf : public ::std::basic_streambuf<Ch,Tr> {
	typedef ::std::ios_base	IOSBASE;
public:
	~basic_win32console_streambuf(void)
    {
        FreeConsole();
    }
    basic_win32console_streambuf(void)
    {
        setbuf(0,0);
        AllocConsole();
		SetConsoleTitle("Win32 Console");
		const SMALL_RECT smallRect = {0,0,60,15};
		SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE),TRUE,&smallRect);
		const COORD coord = {80,20000};
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),coord);
		
	}
	basic_win32console_streambuf( basic_win32console_streambuf const &stream ){
	}
	basic_win32console_streambuf & operator=( basic_win32console_streambuf const  &stream ){
		return stream;
	}
protected:
	::std::streampos seekoff( 
		::std::streamoff off, 
		::std::ios::seek_dir dir,
		int nMode = IOSBASE::in | IOSBASE::out )
    {
        return Tr::eof();
    }
	::std::streampos seekpos( 
		::std::streampos pos, 
		int nMode = IOSBASE::in | IOSBASE::out )
    {
        return Tr::eof();
    }

    int_type overflow( int_type nCh = Tr::eof() )
    {
		Ch buffer[2];
		buffer[0]=nCh;
        DWORD size;
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE),buffer,1,&size,NULL);
        return 0;
    }

    int_type underflow(void)
    {
        return Tr::eof();
    }

};



template <class Ch,class Tr=::std::char_traits<Ch> >
class basic_win32console_stream : public ::std::basic_iostream<Ch,Tr> {
public:
	// TODO : classlevellockÇé©çÏÇÃÇ‡ÇÃÇ…íuÇ´ä∑Ç¶ÇÈÇ©Ç‡ÅB
	basic_win32console_stream(void) 
		: ::std::basic_iostream<Ch,Tr>( &Loki::SingletonHolder< basic_win32console_streambuf<Ch,Tr> , Loki::CreateUsingNew , Loki::PhoenixSingleton >::Instance() )
    {
    }

    ~basic_win32console_stream(void)
    {
    }

private:

};
 
typedef basic_win32console_streambuf<char> win32console_streambuf;
typedef basic_win32console_stream<char> win32console_stream;

}
}
