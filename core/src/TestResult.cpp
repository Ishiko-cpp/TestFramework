/*
    Copyright (c) 2019 Xavier Leclercq
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
    case TestResult::eUnknown:
        str = "unknown";
        break;

    case TestResult::ePassed:
        str = "passed";
        break;

    case TestResult::ePassedButMemoryLeaks:
        str = "memory leak detected";
        break;

    case TestResult::eException:
        str = "exception";
        break;

    case TestResult::eFailed:
        str = "failed";
        break;

    default:
        str = "UNEXPECTED OUTCOME ENUM VALUE";
        break;
    }
    return str;
}

}
}
