#ifndef __CHECKINGPOLICY_H__
#define __CHECKINGPOLICY_H__

#include "NullPointerException.h"

namespace zefiro {
namespace std {
    template <class P>
    struct RejectNull
    {
        RejectNull()
        {}
        
        template <class P1>
        RejectNull(const RejectNull<P1>&)
        {}
        
        static void OnInit(P val)
        { if (!val) throw NullPointerException();  }

        static void OnDefault(P val)
        {}
        
        void OnDereference(P val)
        { if (!val) throw NullPointerException();  }
        
        void Swap(RejectNull&)
        {}        
    };
}
}

#endif //__CHECKINGPOLICY_H__