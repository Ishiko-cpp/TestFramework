/*
    Copyright (c) 2019-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "TestResult.h"

namespace Ishiko
{
namespace Tests
{

std::string ToString(TestResult result)
{
    std::string str;
    switch (result)
    {
    case TestResult::unknown:
        str = "unknown";
        break;

    case TestResult::passed:
        str = "passed";
        break;

    case TestResult::passedButMemoryLeaks:
        str = "memory leak detected";
        break;

    case TestResult::exception:
        str = "exception";
        break;

    case TestResult::failed:
        str = "failed";
        break;

    case TestResult::skipped:
        str = "skipped";
        break;

    default:
        str = "UNEXPECTED OUTCOME ENUM VALUE";
        break;
    }
    return str;
}

}
}
