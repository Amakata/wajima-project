/**
 * $Header: /home/zefiro/cvsrep/cpp/wajima/src/lib/system/ThreadingModel.h,v 1.4 2002/11/17 10:28:37 ama Exp $
 */
#ifndef __THREADINGMODEL_H__
#define __THREADINGMODEL_H__

namespace zefiro {
namespace system{
#ifdef _WINDOWS_
    template <class Host>
    class ObjectLevelCountedLockable
    {
        CRITICAL_SECTION mtx_;
		volatile unsigned int cnt_;
    public:
		ObjectLevelCountedLockable():cnt_(0)
        {
            ::InitializeCriticalSection(&mtx_);
		}

        ~ObjectLevelCountedLockable()
        {
			::DeleteCriticalSection(&mtx_);
        }

        class Lock;
        friend class Lock;
        
        class Lock
        {
            ObjectLevelCountedLockable& host_;
            
            Lock(const Lock&);
            Lock& operator=(const Lock&);
        public:
            explicit Lock(ObjectLevelCountedLockable& host) : host_(host)
            {
                ::EnterCriticalSection(&host_.mtx_);
				::InterlockedIncrement( reinterpret_cast<LONG*>(const_cast<unsigned int*>(&host_.cnt_)) );
            }
            ~Lock()
            {
				::InterlockedDecrement( reinterpret_cast<LONG*>(const_cast<unsigned int*>(&host_.cnt_)));
				::LeaveCriticalSection(&host_.mtx_);
            }
        };

		class Unlock;
		friend class Unlock;

		class Unlock
		{
            ObjectLevelCountedLockable& host_;
			unsigned int cnt_;			
			Unlock(const Unlock&);
			Unlock& operator=(const Unlock&);
		public:
			explicit Unlock(ObjectLevelCountedLockable& host) : host_(host)
			{
				cnt_ = host_.cnt_;
				for(unsigned int i=0;i<cnt_;++i){
					::InterlockedDecrement(reinterpret_cast<LONG*>(const_cast<unsigned int*>(&host_.cnt_)));
					::LeaveCriticalSection(&host_.mtx_);
				}
			}
            ~Unlock()
            {
				for(unsigned int i=0;i<cnt_;++i){
					::EnterCriticalSection(&host_.mtx_);
					::InterlockedIncrement(reinterpret_cast<LONG*>(const_cast<unsigned int*>(&host_.cnt_)));
				}
            }
		};

        typedef volatile Host VolatileType;

        typedef LONG IntType; 

        static IntType AtomicIncrement(volatile IntType& lval)
        { return InterlockedIncrement(&const_cast<IntType&>(lval)); }
        
        static IntType AtomicDecrement(volatile IntType& lval)
        { return InterlockedDecrement(&const_cast<IntType&>(lval)); }
        
        static void AtomicAssign(volatile IntType& lval, IntType val)
        { InterlockedExchange(&const_cast<IntType&>(lval), val); }
        
        static void AtomicAssign(IntType& lval, volatile IntType& val)
        { InterlockedExchange(&lval, val); }
    };
    
    template <class Host>
    class ClassLevelCountedLockable
		{
        struct Initializer
        {   
            CRITICAL_SECTION mtx_;
			unsigned int cnt_;
			Initializer():cnt_(0)
            {
                ::InitializeCriticalSection(&mtx_);
            }
            ~Initializer()
            {
                ::DeleteCriticalSection(&mtx_);
            }
        };
        
        static Initializer initializer_;

    public:
        class Lock;
        friend class Lock;
        
        class Lock
        {
            Lock(const Lock&);
            Lock& operator=(const Lock&);
        public:
            Lock()
            {
                ::EnterCriticalSection(&initializer_.mtx_);
				::InterlockedIncrement(reinterpret_cast<LONG*>(const_cast<unsigned int*>(&initializer_.cnt_)));
			}
            explicit Lock(ClassLevelCountedLockable&)
            {
                ::EnterCriticalSection(&initializer_.mtx_);
				::InterlockedIncrement(reinterpret_cast<LONG*>(const_cast<unsigned int*>(&initializer_.cnt_)));
            }
            ~Lock()
            {
				::InterlockedDecrement(reinterpret_cast<LONG*>(const_cast<unsigned int*>(&initializer_.cnt_)));
				::LeaveCriticalSection(&initializer_.mtx_);
            }
        };

        class Unlock;
        friend class Unlock;
        
        class Unlock
        {
            Unlock(const Unlock&);
            Unlock& operator=(const Unlock&);
			unsigned int cnt_;
		public:
            Unlock()
            {
				cnt_ = initializer_.cnt_;
				for(unsigned int i=0;i<cnt_;++i){
					::InterlockedDecrement(reinterpret_cast<LONG*>(const_cast<unsigned int*>(&initializer_.cnt_)));
					::LeaveCriticalSection(&initializer_.mtx_);
				}
			}
            explicit Unlock(ClassLevelCountedLockable&)
            {
				cnt_ = initializer_.cnt_;
				for(unsigned int i=0;i<cnt_;++i){
					::InterlockedDecrement(reinterpret_cast<LONG*>(const_cast<unsigned int*>(&initializer_.cnt_)));
					::LeaveCriticalSection(&initializer_.mtx_);
				}
            }
            ~Unlock()
            {
				for(unsigned int i=0;i<cnt_;++i){
	                ::EnterCriticalSection(&initializer_.mtx_);
					::InterlockedIncrement(reinterpret_cast<LONG*>(const_cast<unsigned int*>(&initializer_.cnt_)));
				}
            }
        };


        typedef volatile Host VolatileType;

        typedef LONG IntType; 

        static IntType AtomicIncrement(volatile IntType& lval)
        { return InterlockedIncrement(&const_cast<IntType&>(lval)); }
        
        static IntType AtomicDecrement(volatile IntType& lval)
        { return InterlockedDecrement(&const_cast<IntType&>(lval)); }
        
        static void AtomicAssign(volatile IntType& lval, IntType val)
        { InterlockedExchange(&const_cast<IntType&>(lval), val); }
        
        static void AtomicAssign(IntType& lval, volatile IntType& val)
        { InterlockedExchange(&lval, val); }
    };
    
    template <class Host>
    typename ClassLevelCountedLockable<Host>::Initializer 
    ClassLevelCountedLockable<Host>::initializer_;
    
#endif    
}
}


#endif //__THREADINGMODEL_H__