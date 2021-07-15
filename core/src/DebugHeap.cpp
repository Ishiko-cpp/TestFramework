/*
    Copyright (c) 2005-2019 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "DebugHeap.h"
#if (defined(_WIN32) && defined(_DEBUG))
#include <crtdbg.h>
#endif

namespace Ishiko
{
namespace Tests
{

DebugHeap::HeapState::HeapState()
{
#if (defined(_WIN32) && defined(_DEBUG))
    _CrtMemState heapState;
    _CrtMemCheckpoint(&heapState);
    m_allocatedSize = heapState.lSizes[_NORMAL_BLOCK];
#else
    m_allocatedSize = 0;
#endif
}

size_t DebugHeap::HeapState::allocatedSize() const
{
    return m_allocatedSize;
}

DebugHeap::TrackingState::TrackingState()
{
#if (defined(_WIN32) && defined(_DEBUG))
    m_flags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
#endif
}

void DebugHeap::TrackingState::disableTracking()
{
#if (defined(_WIN32) && defined(_DEBUG))
    int newFlags = (m_flags & ~_CRTDBG_ALLOC_MEM_DF);
    _CrtSetDbgFlag(newFlags);
#endif
}

void DebugHeap::TrackingState::restore()
{
#if (defined(_WIN32) && defined(_DEBUG))
    _CrtSetDbgFlag(m_flags);
#endif
}

}
}
