/*
    Copyright (c) 2005-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTFRAMEWORK_CORE_DEBUGHEAP_HPP_
#define _ISHIKO_CPP_TESTFRAMEWORK_CORE_DEBUGHEAP_HPP_

#include <cstddef>

namespace Ishiko
{

class DebugHeap
{
public:
    class HeapState
    {
    public:
        HeapState();

        size_t allocatedSize() const;

    private:
        size_t m_allocatedSize;
    };

    class TrackingState
    {
    public:
        TrackingState();

        void disableTracking();
        void restore();

#if (defined(_WIN32) && defined(_DEBUG))
    private:
        int m_flags;
#endif
    };
};

}

#endif
