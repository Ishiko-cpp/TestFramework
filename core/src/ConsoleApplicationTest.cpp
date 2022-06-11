/*
    Copyright (c) 2016-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "ConsoleApplicationTest.hpp"
#include "TestMacros.hpp"
#include <Ishiko/Process.hpp>

namespace Ishiko
{

ConsoleApplicationTest::ConsoleApplicationTest(const TestNumber& number, const std::string& name,
    const std::string& commandLine, int expectedExitCode)
    : Test(number, name), m_commandLine(commandLine), m_checkExitCode(true), m_expectedExitCode(expectedExitCode)
{
}

ConsoleApplicationTest::ConsoleApplicationTest(const TestNumber& number, const std::string& name,
    const std::string& commandLine, int expectedExitCode, const TestContext& context)
    : Test(number, name, context), m_commandLine(commandLine), m_checkExitCode(true),
    m_expectedExitCode(expectedExitCode)
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

// TODO: this is used the test macros but I probably want custom error messages
void ConsoleApplicationTest::doRun()
{
    // The test macros rely a variable called "test" to be defined.
    Test& test = *this;

    ChildProcessBuilder processCreator(m_commandLine);
    if (!m_standardOutputTest.outputFilePath().empty())
    {
        processCreator.redirectStandardOutputToFile(m_standardOutputTest.outputFilePath().string());
    }

    Error error;
    ChildProcess processHandle = processCreator.start(error);

    ISHIKO_TEST_ABORT_IF(error);
    
    processHandle.waitForExit();

    if (m_checkExitCode)
    {
        ISHIKO_TEST_FAIL_IF_NEQ(processHandle.exitCode(), m_expectedExitCode);
    }

    if (!m_standardOutputTest.outputFilePath().empty() && !m_standardOutputTest.referenceFilePath().empty())
    {
        m_standardOutputTest.run(test, __FILE__, __LINE__);
    }

    ISHIKO_TEST_PASS();
}

}
