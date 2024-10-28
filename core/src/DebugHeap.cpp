// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "DebugHeap.hpp"
#if ((ISHIKO_RUNTIME == ISHIKO_RUNTIME_MICROSOFT_CRT) && defined(_DEBUG))
#include <crtdbg.h>
#endif

using namespace Ishiko;

Ishiko::DebugHeap::HeapState::HeapState()
{
#if ((ISHIKO_RUNTIME == ISHIKO_RUNTIME_MICROSOFT_CRT) && defined(_DEBUG))
    _CrtMemState heapState;
    _CrtMemCheckpoint(&heapState);
    m_allocatedSize = heapState.lSizes[_NORMAL_BLOCK];
#else
    m_allocatedSize = 0;
#endif
}

size_t Ishiko::DebugHeap::HeapState::allocatedSize() const
{
    return m_allocatedSize;
}

Ishiko::DebugHeap::TrackingState::TrackingState()
{
#if ((ISHIKO_RUNTIME == ISHIKO_RUNTIME_MICROSOFT_CRT) && defined(_DEBUG))
    m_flags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
#endif
}

void Ishiko::DebugHeap::TrackingState::disableTracking()
{
#if ((ISHIKO_RUNTIME == ISHIKO_RUNTIME_MICROSOFT_CRT) && defined(_DEBUG))
    int newFlags = (m_flags & ~_CRTDBG_ALLOC_MEM_DF);
    _CrtSetDbgFlag(newFlags);
#endif
}

void Ishiko::DebugHeap::TrackingState::restore()
{
#if ((ISHIKO_RUNTIME == ISHIKO_RUNTIME_MICROSOFT_CRT) && defined(_DEBUG))
    _CrtSetDbgFlag(m_flags);
#endif
}
