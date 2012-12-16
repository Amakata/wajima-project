/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/Thread.h,v 1.5 2002/11/07 16:58:21 ama Exp $
 */

#ifndef __THREAD_H__
#define __THREAD_H__

#include <windows.h>
#include <string>
#include <vector>

#include "Runnable.h"
#include "Mutex.h"
#include "IllegalThreadStateException.h"
#include "TimeOutException.h"
#include "std/sys/Win32Assert.h"
#include "ThreadingModel.h"

namespace zefiro {
namespace system {
	// TODO: スレッド終了時のコールバック関数を追加できるようにすべきかも。
	// TODO: threadsはシングルトンにしておくべきかも。
	class Thread : public Runnable , public ObjectLevelCountedLockable<Thread>
	{
	public:
		/**
		 * コンストラクタ
		 * \param stackSize スレッドで確保するスタックのサイズ(0にすると、呼び出し側スレッドと同じサイズになる。)
		 * \param name スレッドにつく名前
		 * \param runnable スレッドで呼び出すrunメソッドのあるオブジェクト、Threadを派生させずに使う場合指定する。
　		 */
		Thread( int stackSize = 0 );
		Thread( ::std::string name , int stackSize = 0 );
		Thread( Runnable *runnable , int stackSize = 0 );
		Thread( Runnable *runnable , ::std::string name , int stackSize = 0 );
		/**
		 * スレッドの利用可能判定
		 * \retval true スレッドオブジェクトは利用可能である。
		 * \retval false 　スレッドオブジェクトは利用不可能である。
		 */
		bool isAvailable();
		/**
		 * スレッドのJoin可能判定
		 * <ul>
		 *  <li>Join可能なスレッドは必ずJoinしなければならない。
		 * もしJoinしない場合は、リソースリークが発生する。</li>
		 *  <li>Join不可能なスレッドはJoinしてはならない。
		 * Join不可能なスレッドオブジェクトはスレッドの終了時(exit)に
		 * メモリ解放される。したがって、start()された後のいかなる時点でも
		 * メモリ解放がされるおそれがあるので、そのレッドオブジェクトにアク
		 * セスすることは危険である。
		 * </li>
		 * </ul>
		 * \retval true Join可能
		 * \retval false Join不可能
		 */
		bool isJoinable();
		/**
		 * スレッドのJoin可能設定。
		 * このメソッドはstart()が呼ばれる前に呼ばなければならない。
		 * \param joinable
		 * <ul>
		 *	<li>true Join可能 </li>
		 *	<li>false Join不可能 </li>
		 * </ul>
		 */
		void setJoinable( bool joinable );
		/**
		 * Runnableオブジェクトの所有権の取得
		 * Joinableでないときに、Runnableを削除するか？
		 */
		bool canRemoveRunnable();
		/**
		 * Runnableオブジェクトの所有権の設定
		 * setJoinableがfalseの時にcanRemoveRunnableがtrueだと、Thread::exit()したときに、
		 * Threadの所有するRunnableをデストラクトする。
		 * それ以外の時にはRunnableはThreadによってデストラクトされない。
		 * \param canRemoveRunnable JoinableでないときにRunnableをデストラクトする。
		 */
		void setCanRemoveRunnable( bool canRemoveRunnable );
		/**
		 * スレッドIDを返す。
		 * \return スレッドID
		 */
		int getThreadID();
		/**
		 * スレッドの名前を返す。
		 * \return スレッドの名前。この名前はユーザがコンストラクタで指定した名前となる。
		 */
		::std::string getName();
		/**
		 * スレッドの優先度を返す。
		 * \return スレッドの優先度
		 * \throw Win32Exception
		 */
		int getPriority();
		/**
		 * スレッドの優先度を設定する。
		 * \param priority スレッドの優先度
		 * \throw Win32Exception
		 */
		void setPriority( int priority );
		/**
		 * スレッドを開始する。
		 * 一度、開始したスレッドを再び開始することはできない。もし再びstartが呼ばれたら、
		 * IllegalThreadStateExceptionが呼ばれる。
		 * \throw IllegalThreadStateException 異常なスレッド状態例外が発生した。
		 * \throw Win32Exception
		 */
		void start();
		/**
		 * スレッドの結合。
		 * スレッドが終了するまで待機する。
		 * スレッドがJoin可能でない場合の動作は不定である。
		 * \param millisecond 最大でmillisecondだけ待機する。
		 * \return スレッド内で、exit()したときの引数exitCodeとなる。
		 * \throw TimeOutException スレッドがmillisecondだけ待機してタイムアウトになったときに発生する。
		 */
		int join();
		int join( int millisecond );
		/**
		 * スレッドのタイムスライスを譲る。
		 */
		static void yield();
		/**
		 * スレッドをスリープする。
		 */
		static void sleep( int millisecond );
		/**
		 * スレッドの終了。
		 * スレッドを直ちに終了させる。
		 * \param exitCode exitCodeはjoin()したときの戻り値となる。
		 * スレッドからexitを呼び出さずにセットされるexitCodeは0である。
		 */
		static void exit( int exitCode );
		/**
		 * 現在のスレッドのスレッドIDを返す。
		 * \return 現在のスレッドのスレッドID
		 */
		static int getCurrentThreadID();
		/**
		 * 現在のスレッドのスレッドオブジェクトを返す。
		 * このスレッドオブジェクトはdeleteしてはならない。
		 * \return 現在のスレッドのスレッドオブジェクト
		 */
		static Thread *getCurrentThread();
		/**
		 * スレッドの実行先。
		 * このメッソドをオーバライドするかRunnableを設定し、スレッドの実行内容を指定する。
		 */
		virtual void run();
		/**
		 * スレッドの状態を文字列として返す。
		 */
		virtual ::std::string toString() const;

		static const int NULLTHREAD;
	protected:
		/**
		 * スレッドをコンストラクトする。
		 */
		void create( int stackSize );
		/**
		 * スレッドをJoinする。
		 */
		int doJoin( int millisecond ); 
		/**
		 * メインスレッド用コンストラクタ
		 */
		Thread( HANDLE thread , unsigned int threadid );
		/**
		 * デストラクタ
		 * スレッドはjoinされるかexitされるまでデストラクトされないので、protectedとする。
		 * このようにすることで、必ずThreadはnewでメモリ確保しなければならなくなる。
		 */
		virtual ~Thread();
		/**
		 * スレッドの実行先。
		 * thread->run()かthread->_runnable->run()を実行する。
		 * \param thread 実行先をもつスレッド
		 * \return 必ず0となる。
		 */
		static int runProc( Thread *thread );
	private:
		class Threads : public ClassLevelCountedLockable< Threads > {
			::std::vector<Thread *> threads_;
		public:
			/**
			 * 登録してあるスレッドを削除する。
			 * \param thread 削除するスレッド
			 */
			void removeThread( Thread *thread ){
				Lock lock;
				::std::vector<Thread*>::iterator end = threads_.end();
				for( ::std::vector<Thread*>::iterator itr = threads_.begin() ; itr != end ; ++itr ){
					if( *itr == thread ){
						threads_.erase( itr );
						return;
					}
				}
			}
			/**
			 * 登録してある現在のスレッドのイテレータを返す。
			 */
			::std::vector<Thread*>::iterator getCurrentThreadIterator(){
				int currentID = getCurrentThreadID();
				::std::vector<Thread*>::iterator end = threads_.end();
				for( ::std::vector<Thread*>::iterator itr = threads_.begin() ; itr != end ; ++itr ){
					if(  (*itr)->getThreadID() == currentID ){
						return itr;
					}
				}
				return end;
			}
			/**
			 * メインスレッドの登録
			*/
			void addMainThread(){
				if( threads_.size() == 0 ){
					Thread *mainThread = new Thread( ::GetCurrentThread() , ::GetCurrentThreadId() );
					addThread( mainThread );
				}
			}

			void addThread( Thread* thread ){
				Lock lock;
				threads_.push_back( thread );
			}
			Thread* getCurrentThread(){ 
				Lock lock;
				addMainThread();
				::std::vector<Thread*>::iterator itr;
				Thread *result;
				if( threads_.end() != (itr = getCurrentThreadIterator() ) ){
					result = (*itr);
				}else{
					result = NULL;
				}
				return result;
			}
		};

		HANDLE	thread_;
		unsigned int	threadID_;
		Runnable *runnable_;
		DWORD	constructError_;
		bool	hasStarted_;
		bool	joinable_;
		bool	canRemoveRunnable_;
		::std::string	name_;
		static Threads threads__;
	};
}
}

#endif //__THREAD_H__