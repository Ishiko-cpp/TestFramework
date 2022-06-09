/*
    Copyright (c) 2005-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "TestHarness.hpp"
#include "JUnitXMLWriter.hpp"
#include "TestProgressObserver.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem.hpp>
#include <Ishiko/Errors.hpp>
#include <iostream>
#include <iomanip>
#include <memory>

using namespace Ishiko;

TestHarness::CommandLineSpecification::CommandLineSpecification()
{
    // TODO: need to support option without default value instead of abusing an empty value
    addNamedOption("junit-xml-test-report", { Ishiko::CommandLineSpecification::OptionType::singleValue, "" });
}

TestHarness::Configuration::Configuration(const Ishiko::Configuration& configuration)
{
    const std::string& junitXMLTestReport = configuration.value("junit-xml-test-report").asString();
    if (!junitXMLTestReport.empty())
    {
        m_junitXMLTestReport = junitXMLTestReport;
    }
}

const boost::optional<std::string>& TestHarness::Configuration::junitXMLTestReport() const
{
    return m_junitXMLTestReport;
}

TestHarness::TestHarness(const std::string& title)
    : m_context(TestContext::DefaultTestContext()), m_topSequence(title, m_context),
    m_timestampOutputDirectory(true)
{
}

TestHarness::TestHarness(const std::string& title, const Configuration& configuration)
    : m_junitXMLTestReport(configuration.junitXMLTestReport()), m_context(TestContext::DefaultTestContext()),
    m_topSequence(title, m_context), m_timestampOutputDirectory(true)
{
}

int TestHarness::run()
{
    std::cout << "Test Suite: " << m_topSequence.name() << std::endl;

    if (m_context.getTestOutputDirectory() != "")
    {
        prepareOutputDirectory();
    }

    int result = runTests();

    return result;
}

TestContext& TestHarness::context()
{
    return m_context;
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
        boost::filesystem::path newOutputDirectory = m_context.getTestOutputDirectory() / currentSecondStr.str();
        m_context.setTestOutputDirectory(newOutputDirectory.string());
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
        if (m_junitXMLTestReport)
        {
            writeJUnitXMLTestReport(*m_junitXMLTestReport);
        }

        if (!m_topSequence.passed() && !m_topSequence.skipped())
        {
            return TestApplicationReturnCode::testFailure;
        }
        else
        {
            return TestApplicationReturnCode::ok;
        }
    }
    catch (...)
    {
        return TestApplicationReturnCode::exception;
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
    size_t skipped = 0;
    size_t total = 0;
    m_topSequence.getPassRate(unknown, passed, passedButMemoryLeaks, exception, failed, skipped, total);
    if (!m_topSequence.passed() && !m_topSequence.skipped())
    {
        std::cout << "Pass rate: " << std::fixed << std::setprecision(2) << (100 * (double)passed / (double)total)
            << "% (" << unknown << " unknown, "
            << passed << " passed, "
            << passedButMemoryLeaks << " passed but with memory leaks, "
            << exception << " threw exceptions, "
            << failed << " failed, "
            << skipped << " skipped, "
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
            << skipped << " skipped, "
            << total << " total)" << std::endl;
        std::cout << std::endl;
        std::cout << "Test Suite passed" << std::endl;
    }
}

void TestHarness::writeJUnitXMLTestReport(const std::string& path)
{
    // TODO: error handling
    Ishiko::Error error;

    boost::filesystem::path reportPath = path;
    boost::filesystem::create_directories(reportPath.parent_path());

    size_t unknown = 0;
    size_t passed = 0;
    size_t passedButMemoryLeaks = 0;
    size_t exception = 0;
    size_t failed = 0;
    size_t skipped = 0;
    size_t total = 0;
    m_topSequence.getPassRate(unknown, passed, passedButMemoryLeaks, exception, failed, skipped, total);

    JUnitXMLWriter writer;
    writer.create(reportPath, error);
    writer.writeTestSuitesStart();
    writer.writeTestSuiteStart(total);

    m_topSequence.traverse(
        [&writer](const Test& test)
        {
            writer.writeTestCaseStart("unknown", test.name());
            writer.writeTestCaseEnd();
        /*
            if (!test.passed())
            {
                const TestSequence* sequence = dynamic_cast<const TestSequence*>(&test);
                // Special case. If the sequence is empty we consider it to be a single unknown test case. If we didn't
                // do that this case would go unreported.
                if (!sequence || (sequence->size() == 0))
                {
                    std::cout << test.name() << " " << ToString(test.result()) << std::endl;
                }
            }*/
        });

    writer.writeTestSuitesEnd();
    writer.writeTestSuitesEnd();
}
