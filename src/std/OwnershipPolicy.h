#ifndef __OWNERSHIPPOLICY_H__
#define __OWNERSHIPPOLICY_H__

#include "loki/SmallObj.h"

namespace zefiro {
namespace std {
	template <class P>
    class NoOwnerRefCounted;

	template <class P>
    class RefCounted
    {
		friend class NoOwnerRefCounted<P>;
	public:
        RefCounted() 
        {
            pCount_ = static_cast<unsigned int*>(Loki::SmallObject<>::operator new(sizeof(unsigned int)));
            assert(pCount_);
            *pCount_ = 1;
        }       
        RefCounted(const RefCounted& rhs)
        : pCount_(rhs.pCount_)
        {}
        // MWCW lacks template friends, hence the following kludge
        template <typename P1>
        RefCounted(const RefCounted<P1>& rhs) 
        : pCount_(reinterpret_cast<const RefCounted&>(rhs).pCount_)
        {
		}     
		template <typename P1>
		RefCounted( const NoOwnerRefCounted<P1>& rhs)
		: pCount_(reinterpret_cast<const NoOwnerRefCounted<P1>&>(rhs).pCount_)
		{
		}
		P Clone(const P& val)
        {
			++*pCount_;
            return val;
        }
        
        bool Release(const P&, bool = false)
        {
			if (!--*pCount_)
            {
				Loki::SmallObject<>::operator delete(pCount_, sizeof(unsigned int));
                return true;
            }
            return false;
        }
        
        void Swap(RefCounted& rhs)
		{ ::std::swap(pCount_, rhs.pCount_); }
    
        enum { destructiveCopy = false };

    private:
        // Data
        unsigned int* pCount_;
    };


	template <class P>
    class NoOwnerRefCounted
    {
		friend class RefCounted<P>;
    public:        
		NoOwnerRefCounted(const NoOwnerRefCounted& rhs) 
        : pCount_(rhs.pCount_)
        {}
        // MWCW lacks template friends, hence the following kludge
        template <typename P1>
        NoOwnerRefCounted(const NoOwnerRefCounted<P1>& rhs) 
        : pCount_(reinterpret_cast<const NoOwnerRefCounted&>(rhs).pCount_)
        {
		}
		template <typename P1>
		NoOwnerRefCounted(const RefCounted<P1>& rhs)
		: pCount_(reinterpret_cast<const RefCounted<P1>&>(rhs).pCount_)
		{
		}

        P Clone(const P& val)
        {
            return val;
        }
        
        bool Release(const P&, bool = false)
        {
			return false;
        }
        
        void Swap(NoOwnerRefCounted& rhs)
		{ ::std::swap(pCount_, rhs.pCount_); }
    
        enum { destructiveCopy = false };

    private:
        // Data
        unsigned int* pCount_;
    };
}
}


#endif //__OWNERSHIPPOLICY_H__