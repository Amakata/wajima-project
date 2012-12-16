#pragma once

#include <iostream>
#include "system/Thread.h"
#include "system/ThreadingModel.h"
#include "system/ThreadLocal.h"
#include "std/win32debug_console_stream.h"

namespace zefiro {
namespace test {

	class ThreadLocalRunnable : public zefiro::system::Runnable , public zefiro_system::ClassLevelCountedLockable<ThreadLocalRunnable>{
public:
	virtual void run(){
		id_ = zefiro::system::Thread::getCurrentThreadID();
		
		zefiro::std::win32debug_console_stream wdcon;
		for( int i=0 ; i<1000 ; ++i ){
			Lock lock(*this);
			if( zefiro::system::Thread::getCurrentThreadID() != id_ ){
				wdcon << "********************** ERROR ******************" << std::endl;
			}
		}
	}
private:
	zefiro::system::ThreadLocal<int>	id_;
};


// ThradLocalRunnableに持たせたThreadLocalに二つのスレッドから自スレッドIDを書き込んで、
// 自スレッドIDと値が変化しないかチェックするテストプログラム
class ThreadLocalTest {
public:
	void start(){
		ThreadLocalRunnable* runnable = new ThreadLocalRunnable();
		zefiro::system::Thread* thread1 = new zefiro::system::Thread(runnable);
		zefiro::system::Thread* thread2 = new zefiro::system::Thread(runnable);

		thread1->start();
		thread2->start();
	}
};

}
}