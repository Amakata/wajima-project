#pragma once

#include <map>
#include <list>
#include "loki/Singleton.h"
#include "system/Thread.h"
#include "system/ThreadingModel.h"

namespace zefiro {
namespace system {


class ThreadLocalBase {
public:
	virtual ~ThreadLocalBase(){}
	virtual void clear() = 0;
	virtual void clear( int threadId ) = 0;
};

class ThreadLocals {
	typedef ::std::list<ThreadLocalBase* > TLBList;
public:
	virtual ~ThreadLocals(){
	}
	void add( ThreadLocalBase* val ){
		threadLocals_.push_back(val);
	}
	void del( ThreadLocalBase* val ){
		threadLocals_.remove( val );
	}
	void clear(){
		int currentThreadId = Thread::getCurrentThreadID();
		TLBList::iterator end = threadLocals_.end();
		for( TLBList::iterator it = threadLocals_.begin() ; it != end ; ++it ){
			(*it)->clear( currentThreadId );
		}
	}
private:
	friend Loki::CreateUsingNew<ThreadLocals>;
	ThreadLocals(){
	}
	TLBList threadLocals_;
};

// �X���b�h�Ɨ��ȕϐ�����������e���v���[�g�N���X
/**

�����̃X���b�h����Q�Ƃ���郁���o�ϐ����X���b�h�Ɨ��ɂ������ꍇ�ȂǂɎg���B
��F
class A{
public:
	void set( int x ){
		val_ = x;	//	set���Ăяo���X���b�h�ɂ����x���i�[�����ꏊ�͈Ⴄ�B�����X���b�h�̏ꍇ�̂ݓ����ϐ��ɃA�N�Z�X�ł���B
	}
	int get(){
		return val_;// get���Ăяo���X���b�h�ɂ����val�̒l�͈Ⴄ�B�����X���b�h�̏ꍇ�̂ݓ����ϐ��ɃA�N�Z�X�ł���B
	}
private:
zefiro::system::ThreadLocal<int> val_;
};
*/
template <typename T>
class ThreadLocal : public ObjectLevelCountedLockable<ThreadLocal> , public ThreadLocalBase {
	typedef ::std::map< int , T* > ThreadLocalMap;
	typedef Loki::SingletonHolder< ThreadLocals ,Loki::CreateUsingNew, Loki::DefaultLifetime,zefiro::system::ClassLevelCountedLockable > SingleThreadLocals;
public:
	ThreadLocal(){
		ThreadLocals& tls = SingleThreadLocals::Instance();
		tls.add( this );
	}
	virtual ~ThreadLocal(){
		ThreadLocals& tls = SingleThreadLocals::Instance();
		tls.del( this );
	}
	operator T&() {
		Lock lock(*this);
		return *get();
	}
	const T& operator = (const T& t){
		Lock lock(*this);
		set(t);
		return *get();
	}
	virtual void clear(){
		Lock lock(*this);
		erase( Thread::getCurrentThreadID() );
	}
	virtual void clear( int threadId ){
		Lock lock(*this);
		erase( threadId );
	}
	bool empty(){
		ThreadLocalMap::iterator it = vals_.find( Thread::getCurrentThreadID() );
		return it == vals_.end();
	}
private:
	T* get(){
		ThreadLocalMap::iterator it = vals_.find( Thread::getCurrentThreadID() );
		T* result;
		if( it != vals_.end() ){
			result = it->second;
		}else{
			result = new T;
			vals_.insert( ::std::pair<int,T* >(Thread::getCurrentThreadID(),result));
		}

		return result;
	}
	void set( const T& t ){
		ThreadLocalMap::iterator it = vals_.find( Thread::getCurrentThreadID() );
		if( it != vals_.end() ){
			*(it->second) = t;
		}else{
			T* p = new T;
			*p = t;
			vals_.insert( ::std::pair<int,T*>(Thread::getCurrentThreadID(),p));
		}
	}
	void erase( int threadId ){
		ThreadLocalMap::iterator it = vals_.find( threadId );
		if( it != vals_.end() ){
			vals_.erase( it );
		}
	}
	ThreadLocalMap	vals_;
};




}
}