/*
    Copyright (c) 2005-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTRESULT_HPP_
#define _ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTRESULT_HPP_

#include <string>

namespace Ishiko
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

#endif
