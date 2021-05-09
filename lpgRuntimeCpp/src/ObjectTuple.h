#pragma once
#include "tuple.h"
struct Object;
typedef Tuple<void* > ObjectTuple;
typedef  Tuple<int> IntSegmentedTuple;

namespace
{
    int binarySearch(IntSegmentedTuple& tuple, int element)
    {
        int low = 0,
            high = tuple.Length();
        while (high > low)
        {
            int mid = (high + low) / 2;
            const int mid_element = tuple.get(mid);
            if (element == mid_element)
                return mid;
            else if (element < mid_element)
                high = mid;
            else low = mid + 1;
        }

        return -low;
    }
}
