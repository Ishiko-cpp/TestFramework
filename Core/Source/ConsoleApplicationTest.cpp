/*
    Copyright (c) 2016 Xavier Leclercq

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
namespace TestFramework
{

ConsoleApplicationTest::ConsoleApplicationTest(const TestNumber& number,
                                               const std::string& name,
                                               const std::string& commandLine,
                                               int expectedExitCode)
    : Test(number, name), m_commandLine(commandLine), m_checkExitCode(true),
    m_expectedExitCode(expectedExitCode)
{
}

ConsoleApplicationTest::~ConsoleApplicationTest()
{
}

TestResult::EOutcome ConsoleApplicationTest::doRun(TestObserver::ptr& observer)
{
    TestResult::EOutcome result = TestResult::eFailed;

    Ishiko::Process::ProcessCreator processCreator(m_commandLine);
    Ishiko::Process::ProcessHandle processHandle;
    if (processCreator.start(processHandle) == 0)
    {
        processHandle.waitForExit();
        if (m_checkExitCode)
        {
            if (processHandle.exitCode() == m_expectedExitCode)
            {
                result = TestResult::ePassed;
            }
        }
    }
    
    return result;
}

}
}
