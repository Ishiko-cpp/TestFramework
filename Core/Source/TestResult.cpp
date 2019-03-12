/*
    Copyright (c) 2019 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
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
