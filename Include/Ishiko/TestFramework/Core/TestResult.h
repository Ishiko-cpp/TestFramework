/*
    Copyright (c) 2005-2019 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_TESTFRAMEWORK_CORE_TESTRESULT_H_
#define _ISHIKO_TESTFRAMEWORK_CORE_TESTRESULT_H_

#include <string>

namespace Ishiko
{
namespace Tests
{

enum class TestResult
{
    eUnknown,
    ePassed,
    ePassedButMemoryLeaks,
    eException,
    eFailed
};

std::string ToString(TestResult result);

}
}

#endif
