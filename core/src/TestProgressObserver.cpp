/*
    Copyright (c) 2015-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "TestProgressObserver.h"
#include "Test.h"
#include <iostream>
#include <sstream>

using namespace std;

namespace Ishiko
{
namespace Tests
{

namespace
{

void WriteNesting(size_t level, ostream& output)
{
    for (size_t i = 0; i < level; ++i)
    {
        output << "    ";
    }
}

}

TestProgressObserver::TestProgressObserver(ostream& output)
    : m_output(output), m_nestingLevel(0)
{
}

void TestProgressObserver::onLifecycleEvent(const Test& source, EEventType type)
{
    switch (type)
    {
    case eTestStart:
        WriteNesting(m_nestingLevel, m_output);
        m_output << formatNumber(source.number()) << " " << source.name() << " started" << endl;
        ++m_nestingLevel;
        break;

    case eTestEnd:
        if (m_nestingLevel > 0)
        {
            --m_nestingLevel;
        }

        WriteNesting(m_nestingLevel, m_output);
        m_output << formatNumber(source.number()) << " " << source.name() << " completed, result is "
            << formatResult(source.result()) << endl;
        break;
    }
}

void TestProgressObserver::onCheckFailed(const Test& source, const string& message, const char* file, int line)
{
    WriteNesting(m_nestingLevel, m_output);
    if (message.empty())
    {
        m_output << "Check failed [file: " << file << ", line: " << line << "]" << endl;
    }
    else
    {
        m_output << "Check failed: " << message << " [file: " << file << ", line: " << line << "]"  << endl;
    }
}

void TestProgressObserver::onExceptionThrown(const Test& source, exception_ptr exception)
{
    WriteNesting(m_nestingLevel, m_output);
    if (exception)
    {
        try
        {
            rethrow_exception(exception);
        }
        catch (const std::exception& e)
        {
            m_output << "Exception thrown: " << e.what() << endl;
        }
        catch (...)
        {
            m_output << "Exception not derived from std::exception thrown" << endl;
        }
    }
    else
    {
        m_output << "Exception thrown but no exception information available" << endl;
    }
}

string TestProgressObserver::formatNumber(const TestNumber& number)
{
    stringstream formattedNumber;

    for (size_t i = 0; i < number.depth(); ++i)
    {
        formattedNumber << number.part(i) << ".";
    }

    return formattedNumber.str();
}

string TestProgressObserver::formatResult(const TestResult& result)
{
    string formattedResult;
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
