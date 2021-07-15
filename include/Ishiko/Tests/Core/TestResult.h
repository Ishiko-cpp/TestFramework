/*
    Copyright (c) 2005-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_CORE_TESTRESULT_H_
#define _ISHIKO_TESTS_CORE_TESTRESULT_H_

#include <string>

namespace Ishiko
{
namespace Tests
{

enum class TestResult
{
    unknown,
    passed,
    passedButMemoryLeaks,
    exception,
    failed,
    skipped
};

std::string ToString(TestResult result);

}
}

#endif
