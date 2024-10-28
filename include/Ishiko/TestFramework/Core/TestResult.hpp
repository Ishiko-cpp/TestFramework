// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTRESULT_HPP
#define GUARD_ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTRESULT_HPP

#include <string>

namespace Ishiko
{

// TODO: make this is an inner class?
enum class TestResult
{
    unknown,
    passed,
    passed_but_memory_leaks,
    exception,
    failed,
    skipped
};

std::string ToString(TestResult result);

}

#endif
