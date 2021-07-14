/*
    Copyright (c) 2005-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_CORE_DBEUGHEAP_H_
#define _ISHIKO_TESTS_CORE_DBEUGHEAP_H_

#include <cstddef>

namespace Ishiko
{
namespace Tests
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
}

#endif
