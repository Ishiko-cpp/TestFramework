/*
    Copyright (c) 2015-2019 Xavier Leclercq

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

#include "TestProgressObserver.h"
#include "Test.h"
#include <iostream>
#include <sstream>

namespace Ishiko
{
namespace Tests
{

void TestProgressObserver::onLifecycleEvent(const Test& source, EEventType type)
{
    switch (type)
    {
    case eTestStart:
        std::cout << m_nesting << formatNumber(source.number()) << " " << source.name() << " started" << std::endl;
        m_nesting.append("    ");
        break;

    case eTestEnd:
        if (!m_nesting.empty())
        {
            m_nesting.erase(m_nesting.size() - 4);
        }

        std::cout << m_nesting << formatNumber(source.number()) << " " << source.name() << " completed, result is "
            << formatResult(source.result()) << std::endl;
        break;
    }
}

void TestProgressObserver::onCheckFailed(const Test& source, const std::string& message, const char* file, int line)
{
    if (message.size() == 0)
    {
        std::cout << m_nesting << "Check failed [file: " << file << ", line: " << line << "]" << std::endl;
    }
    else
    {
        std::cout << m_nesting << "Check failed: " << message << " [file: " << file << ", line: " << line << "]" 
            << std::endl;
    }
}

std::string TestProgressObserver::formatNumber(const TestNumber& number)
{
    std::stringstream formattedNumber;

    for (size_t i = 0; i < number.depth(); ++i)
    {
        formattedNumber << number.part(i) << ".";
    }

    return formattedNumber.str();
}

std::string TestProgressObserver::formatResult(const TestResult& result)
{
    std::string formattedResult;
    switch (result)
    {
    case TestResult::eUnknown:
        formattedResult = "UNKNOWN!!!";
        break;

    case TestResult::ePassed:
        formattedResult = "passed";
        break;

    case TestResult::ePassedButMemoryLeaks:
        formattedResult = "MEMORY LEAK DETECTED";
        break;

    case TestResult::eException:
        formattedResult = "EXCEPTION!!!";
        break;

    case TestResult::eFailed:
        formattedResult = "FAILED!!!";
        break;

    default:
        formattedResult = "UNEXPECTED OUTCOME ENUM VALUE";
        break;
    }
    return formattedResult;
}

}
}
