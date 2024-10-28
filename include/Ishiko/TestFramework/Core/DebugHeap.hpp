// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_TESTFRAMEWORK_CORE_DEBUGHEAP_HPP
#define GUARD_ISHIKO_CPP_TESTFRAMEWORK_CORE_DEBUGHEAP_HPP

#include <Ishiko/BasePlatform.hpp>
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

            size_t allocationCount() const;
            size_t allocatedSize() const;

        private:
            size_t m_allocation_count;
            size_t m_allocated_size;
        };

        class TrackingState
        {
        public:
            TrackingState();

            void disableTracking();
            void restore();

#if ((ISHIKO_RUNTIME == ISHIKO_RUNTIME_MICROSOFT_CRT) && defined(_DEBUG))
        private:
            int m_flags;
#endif
        };
    };
}

#endif
