#pragma once

#include <windows.h>
#include <iostream>
#include <ios>

namespace zefiro {
namespace std {

// sjis‘Î‰ž
template <class Ch,class Tr=::std::char_traits<Ch> >
class basic_win32debug_console_streambuf : public ::std::basic_streambuf<Ch,Tr> {
	typedef ::std::ios_base	IOSBASE;
public:
	basic_win32debug_console_streambuf(void):buffer_()
    {
        setbuf(0,0);
    }
    ~basic_win32debug_console_streambuf(void)
    {
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
		buffer_.push(nCh);
		return 0;
    }

	int_type underflow(void)
    {
        return Tr::eof();
    }

private:
	class Buffer{
	public:
		Buffer(){
			clear();
		}
		virtual ~Buffer(){
		}
		void clear(){
			buffer_[0] = 0;
			buffer_[1] = 0;
			buffer_[2] = 0;
			size_ = 0;
		}
		void push( char c ){
			buffer_[size_] = c;
			++size_;
			if( isSJIS(c) && size_ < 2 ){
				return;
			}else{
				OutputDebugString(buffer_);
				clear();
			}
		}
	protected:
		bool isSJIS( char c ) const{
			if(
				(
					(((unsigned char)(c))>=0x81) &&
					(((unsigned char)(c))<=0x9F)
				)||
				(
					(((unsigned char)(c))>=0xE0) &&
					(((unsigned char)(c))<=0xFC)
				)
			){
				return true;
			}else{
				return false;
			}

		}
	private:
		char buffer_[3];
		int size_;
	};
	Buffer buffer_;
};

template <class Ch,class Tr=::std::char_traits<Ch> >
class basic_win32debug_console_stream : public ::std::basic_iostream<Ch,Tr> {
public:
    basic_win32debug_console_stream(void) 
		: ::std::basic_iostream<Ch,Tr>(new basic_win32debug_console_streambuf<Ch,Tr>())
    {
    }

    ~basic_win32debug_console_stream(void)
    {
    }

private:

};

typedef basic_win32debug_console_streambuf<char> win32debug_console_streambuf;
typedef basic_win32debug_console_stream<char> win32debug_console_stream;

}
}