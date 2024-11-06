// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "ConsoleApplicationTest.hpp"
#include "TestMacros.hpp"
#include <Ishiko/Process.hpp>

using namespace Ishiko;

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

ConsoleApplicationTest::ConsoleApplicationTest(const TestNumber& number, const std::string& name,
    const std::string& command_line, std::function<void(int exit_code, ConsoleApplicationTest& test)> run_fct,
    const TestContext& context)
    : Test(number, name, context), m_commandLine(command_line), m_checkExitCode(false), m_run_fct(run_fct)
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

    if (m_run_fct)
    {
        m_run_fct(processHandle.exitCode(), *this);
    }
    else
    {
        ISHIKO_TEST_PASS();
    }
}
