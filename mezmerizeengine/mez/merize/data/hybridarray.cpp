#include "hybridarray.h"

#if 0
int hybridarray_base::arraysafety(int spot)
{
    bool in_bounds = spot >= 0 && spot < size();
    assert(in_bounds);

    //if we pass the assertion (someone hit continue)
    if (!in_bounds)
    {
        if (spot <= 0) spot = 0;
        if (spot >= size()) spot = size();

        //prevent ANYTHING bad happening
#if !_DEBUG
        abort();
#endif
    }
    return spot;
}

#endif