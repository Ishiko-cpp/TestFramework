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

#include "ConsoleApplicationTestTests.h"

void AddConsoleApplicationTestTests(TestHarness& theTestHarness)
{
    TestSequence& consoleApplicationTestTestSequence =
        theTestHarness.appendTestSequence("ConsoleApplicationTest tests");

    new HeapAllocationErrorsTest("Creation test 1",
        ConsoleApplicationTestCreationTest1, consoleApplicationTestTestSequence);
    
    new HeapAllocationErrorsTest("run success test 1",
        ConsoleApplicationTestRunSuccessTest1, consoleApplicationTestTestSequence);
    new HeapAllocationErrorsTest("run failure test 1",
        ConsoleApplicationTestRunFailureTest1, consoleApplicationTestTestSequence);
    new HeapAllocationErrorsTest("run success test 2",
        ConsoleApplicationTestRunSuccessTest2, consoleApplicationTestTestSequence);
    new HeapAllocationErrorsTest("run failure test 2",
        ConsoleApplicationTestRunFailureTest2, consoleApplicationTestTestSequence);
}

TestResult::EOutcome ConsoleApplicationTestCreationTest1(Test& test)
{
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Binaries/WriteFileTestHelper.exe");

    ConsoleApplicationTest applicationTest(TestNumber(), "ConsoleApplicationTestCreationTest1",
        executablePath.string().c_str(), 0);

    return Ishiko::TestFramework::TestResult::ePassed;
}

TestResult::EOutcome ConsoleApplicationTestRunSuccessTest1(Test& test)
{
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Binaries/ExiCodeTestHelper.exe");

    ConsoleApplicationTest applicationTest(TestNumber(), "ConsoleApplicationTestCreationTest1",
        executablePath.string().c_str(), 0);
    applicationTest.run();

    if (applicationTest.result().passed())
    {
        return Ishiko::TestFramework::TestResult::ePassed;
    }
    else
    {
        return Ishiko::TestFramework::TestResult::eFailed;
    }
}

TestResult::EOutcome ConsoleApplicationTestRunFailureTest1(Test& test)
{
    return Ishiko::TestFramework::TestResult::eFailed;
}

TestResult::EOutcome ConsoleApplicationTestRunSuccessTest2(Test& test)
{
    boost::filesystem::path executablePath(test.environment().getTestDataDirectory() / "Binaries/StandardOutputTestHelper.exe");

    ConsoleApplicationTest applicationTest(TestNumber(), "ConsoleApplicationTestCreationTest2",
        executablePath.string().c_str(), 0);
    applicationTest.run();

    if (applicationTest.result().passed())
    {
        return Ishiko::TestFramework::TestResult::ePassed;
    }
    else
    {
        return Ishiko::TestFramework::TestResult::eFailed;
    }
}

TestResult::EOutcome ConsoleApplicationTestRunFailureTest2(Test& test)
{
    return Ishiko::TestFramework::TestResult::eFailed;
}
