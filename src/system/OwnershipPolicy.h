#pragma once

#include "loki/SmallObj.h"

namespace zefiro {
namespace system {
    template <template <class> class ThreadingModel>
    struct RefCountedMTAdj
    {
        template <class P>
        class RefCountedMT : public ThreadingModel< RefCountedMT<P> >
        {
            typedef ThreadingModel< RefCountedMT<P> > base_type;
            typedef typename base_type::IntType       CountType;
            typedef volatile CountType               *CountPtrType;

        public:
            RefCountedMT() 
            {
                pCount_ = new CountType;
                assert(pCount_);
                *pCount_ = 1;
            }

            RefCountedMT(const RefCountedMT& rhs) 
            : pCount_(rhs.pCount_)
            {}

            //MWCW lacks template friends, hence the following kludge
            template <typename P1>
            RefCountedMT(const RefCountedMT<P1>& rhs) 
            : pCount_(reinterpret_cast<const RefCountedMT<P>&>(rhs).pCount_)
            {}

            P Clone(const P& val)
            {
				Lock lock(*this);
                ThreadingModel<RefCountedMT>::AtomicIncrement(*pCount_);
                return val;
            }

            bool Release(const P&)
            {
				Lock lock(*this);
                if (!ThreadingModel<RefCountedMT>::AtomicDecrement(*pCount_))
                {
					delete  pCount_;
                    return true;
                }
                return false;
            }

            void Swap(RefCountedMT& rhs)
			{ 	Lock lock(*this);
				::std::swap(pCount_, rhs.pCount_);
			}

            enum { destructiveCopy = false };

        private:
            // Data
            CountPtrType pCount_;
        };
    };
}
}