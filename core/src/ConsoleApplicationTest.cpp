/*
    Copyright (c) 2016-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "ConsoleApplicationTest.hpp"
#include "Ishiko/Process/ChildProcessBuilder.h"

namespace Ishiko
{

ConsoleApplicationTest::ConsoleApplicationTest(const TestNumber& number, const std::string& name,
    const std::string& commandLine, int expectedExitCode)
    : Test(number, name), m_commandLine(commandLine), m_checkExitCode(true), m_expectedExitCode(expectedExitCode),
    m_standardOutputTest(TestNumber(), "Standard Output")
{
}

ConsoleApplicationTest::ConsoleApplicationTest(const TestNumber& number, const std::string& name,
    const std::string& commandLine, int expectedExitCode, const TestContext& context)
    : Test(number, name, context), m_commandLine(commandLine), m_checkExitCode(true),
    m_expectedExitCode(expectedExitCode), m_standardOutputTest(TestNumber(), "Standard Output")
{
}

void ConsoleApplicationTest::setStandardOutputFilePath(const boost::filesystem::path& path)
{
    m_standardOutputTest.setOutputFilePath(path);
}

void ConsoleApplicationTest::setStandardOutputReferenceFilePath(const boost::filesystem::path& path)
{
    m_standardOutputTest.setReferenceFilePath(path);
}

void ConsoleApplicationTest::doRun()
{
    TestResult result = TestResult::failed;

    ChildProcessBuilder processCreator(m_commandLine);
    if (!m_standardOutputTest.getOutputFilePath().empty())
    {
        processCreator.redirectStandardOutputToFile(m_standardOutputTest.getOutputFilePath().string());
    }

    Error error(0);
    ChildProcess processHandle = processCreator.start(error);
    if (!error)
    {
        processHandle.waitForExit();

        bool exitCodeTestPassed = false;
        if (m_checkExitCode)
        {
            if (processHandle.exitCode() == m_expectedExitCode)
            {
                exitCodeTestPassed = true;
            }
        }
        else
        {
            exitCodeTestPassed = true;
        }

        bool standardOutputTestPassed = false;
        if (!m_standardOutputTest.getOutputFilePath().empty() &&
            !m_standardOutputTest.getReferenceFilePath().empty())
        {
            m_standardOutputTest.run();
            if (m_standardOutputTest.passed())
            {
                standardOutputTestPassed = true;
            }
        }
        else
        {
            standardOutputTestPassed = true;
        }

        if (exitCodeTestPassed && standardOutputTestPassed)
        {
            result = TestResult::passed;
        }
    }
    
    setResult(result);
}

}
