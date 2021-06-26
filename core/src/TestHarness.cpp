/*
    Copyright (c) 2005-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test/blob/main/LICENSE.txt
*/

#include "TestHarness.h"
#include "TestProgressObserver.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <iomanip>
#include <memory>

namespace Ishiko
{
namespace Tests
{

TestHarness::TestHarness(const std::string& title)
    : m_environment(TestEnvironment::DefaultTestEnvironment()), m_topSequence(title, m_environment),
    m_timestampOutputDirectory(true)
{
}

int TestHarness::run()
{
    std::cout << "Test Suite: " << m_topSequence.name() << std::endl;

    if (m_environment.getTestOutputDirectory() != "")
    {
        prepareOutputDirectory();
    }

    int result = runTests();

    return result;
}

TestEnvironment& TestHarness::environment()
{
    return m_environment;
}

TestSequence& TestHarness::tests()
{
    return m_topSequence;
}

void TestHarness::prepareOutputDirectory()
{
    if (m_timestampOutputDirectory)
    {
        boost::posix_time::ptime currentSecond = boost::posix_time::second_clock::universal_time();
        std::stringstream currentSecondStr;
        currentSecondStr << currentSecond.date().year()
            << std::setw(2) << std::setfill('0') << currentSecond.date().month().as_number()
            << std::setw(2) << std::setfill('0') << currentSecond.date().day() << "T"
            << std::setw(2) << std::setfill('0') << currentSecond.time_of_day().hours()
            << std::setw(2) << std::setfill('0') << currentSecond.time_of_day().minutes()
            << std::setw(2) << std::setfill('0') << currentSecond.time_of_day().seconds() << "Z";
        boost::filesystem::path newOutputDirectory = m_environment.getTestOutputDirectory() / currentSecondStr.str();
        m_environment.setTestOutputDirectory(newOutputDirectory.string());
    }
}

int TestHarness::runTests()
{
    try
    {
        std::shared_ptr<TestProgressObserver> progressObserver = std::make_shared<TestProgressObserver>(std::cout);
        m_topSequence.observers().add(progressObserver);

        std::cout << std::endl;
        m_topSequence.run();
        std::cout << std::endl;

        printDetailedResults();
        printSummary();

        if (!m_topSequence.passed())
        {
            return eTestFailure;
        }
        else
        {
            return eOK;
        }
    }
    catch (...)
    {
        return eException;
    }
}

void TestHarness::printDetailedResults()
{
    m_topSequence.traverse(
        [](const Test& test) -> void
        {
            if (!test.passed())
            {
                const TestSequence* sequence = dynamic_cast<const TestSequence*>(&test);
                // Special case. If the sequence is empty we consider it to be a single unknown test case. If we didn't
                // do that this case would go unreported.
                if (!sequence || (sequence->size() == 0))
                {
                    std::cout << test.name() << " " << ToString(test.result()) << std::endl;
                }
            }
        });
}

void TestHarness::printSummary()
{
    size_t unknown = 0;
    size_t passed = 0;
    size_t passedButMemoryLeaks = 0;
    size_t exception = 0;
    size_t failed = 0;
    size_t total = 0;
    m_topSequence.getPassRate(unknown, passed, passedButMemoryLeaks, exception, failed, total);
    if (!m_topSequence.passed())
    {
        std::cout << "Pass rate: " << std::fixed << std::setprecision(2) << (100 * (double)passed / (double)total)
            << "% (" << unknown << " unknown, "
            << passed << " passed, "
            << passedButMemoryLeaks << " passed but with memory leaks, "
            << exception << " threw exceptions, "
            << failed << " failed, "
            << total << " total)" << std::endl;
        std::cout << std::endl;
        std::cout << "Test Suite FAILED!!!" << std::endl;
    }
    else
    {
        std::cout << "Pass rate: " << std::fixed << std::setprecision(2) << (100 * (double)passed / (double)total)
            << "% (" << unknown << " unknown, "
            << passed << " passed, "
            << passedButMemoryLeaks << " passed but with memory leaks, "
            << exception << " threw exceptions, "
            << failed << " failed, "
            << total << " total)" << std::endl;

        std::cout << std::endl;
        std::cout << "Test Suite passed" << std::endl;
    }
}

}
}
