/*
    Copyright (c) 2015-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "TestProgressObserver.h"
#include "Test.h"
#include <iostream>
#include <sstream>

namespace Ishiko
{
namespace Tests
{

TestProgressObserver::TestProgressObserver(std::ostream& output)
    : m_output(output)
{
}

void TestProgressObserver::onLifecycleEvent(const Test& source, EEventType type)
{
    switch (type)
    {
    case eTestStart:
        m_output << m_nesting << formatNumber(source.number()) << " " << source.name() << " started" << std::endl;
        m_nesting.append("    ");
        break;

    case eTestEnd:
        if (!m_nesting.empty())
        {
            m_nesting.erase(m_nesting.size() - 4);
        }

        m_output << m_nesting << formatNumber(source.number()) << " " << source.name() << " completed, result is "
            << formatResult(source.result()) << std::endl;
        break;
    }
}

void TestProgressObserver::onCheckFailed(const Test& source, const std::string& message, const char* file, int line)
{
    if (message.empty())
    {
        m_output << m_nesting << "Check failed [file: " << file << ", line: " << line << "]" << std::endl;
    }
    else
    {
        m_output << m_nesting << "Check failed: " << message << " [file: " << file << ", line: " << line << "]"
            << std::endl;
    }
}

void TestProgressObserver::onExceptionThrown(const Test& source, std::exception_ptr exception)
{
    if (exception)
    {
        try
        {
            std::rethrow_exception(exception);
        }
        catch (const std::exception& e)
        {
            m_output << m_nesting << "Exception thrown: " << e.what() << std::endl;
        }
        catch(...)
        {
            m_output << m_nesting << "Exception not derived from std::exception thrown" << std::endl;
        }
    }
    else
    {
        m_output << m_nesting << "Exception thrown but no exception information available" << std::endl;
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
    case TestResult::unknown:
        formattedResult = "UNKNOWN!!!";
        break;

    case TestResult::passed:
        formattedResult = "passed";
        break;

    case TestResult::passedButMemoryLeaks:
        formattedResult = "MEMORY LEAK DETECTED";
        break;

    case TestResult::exception:
        formattedResult = "EXCEPTION!!!";
        break;

    case TestResult::failed:
        formattedResult = "FAILED!!!";
        break;

    case TestResult::skipped:
        formattedResult = "skipped";
        break;

    default:
        formattedResult = "UNEXPECTED OUTCOME ENUM VALUE";
        break;
    }
    return formattedResult;
}

}
}
