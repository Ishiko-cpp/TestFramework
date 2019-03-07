/*
    Copyright (c) 2016-2019 Xavier Leclercq

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

#include "ConsoleApplicationTest.h"
#include "Ishiko/Process/ProcessCreator.h"

namespace Ishiko
{
namespace Tests
{

ConsoleApplicationTest::ConsoleApplicationTest(const TestNumber& number, const std::string& name,
    const std::string& commandLine, int expectedExitCode)
    : Test(number, name), m_commandLine(commandLine), m_checkExitCode(true), m_expectedExitCode(expectedExitCode),
    m_standardOutputTest(TestNumber(), "Standard Output")
{
}

ConsoleApplicationTest::ConsoleApplicationTest(const TestNumber& number, const std::string& name,
    const std::string& commandLine, int expectedExitCode, const TestEnvironment& environment)
    : Test(number, name, environment), m_commandLine(commandLine), m_checkExitCode(true),
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
    TestResult result = TestResult::eFailed;

    Ishiko::Process::ProcessCreator processCreator(m_commandLine);
    if (!m_standardOutputTest.getOutputFilePath().empty())
    {
        processCreator.redirectStandardOutputToFile(m_standardOutputTest.getOutputFilePath().string());
    }

    Ishiko::Process::ProcessHandle processHandle;
    if (processCreator.start(processHandle) == 0)
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
            result = TestResult::ePassed;
        }
    }
    
    setResult(result);
}

}
}
