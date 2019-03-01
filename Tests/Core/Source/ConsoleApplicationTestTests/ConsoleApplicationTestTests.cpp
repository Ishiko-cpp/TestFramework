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

#include "ConsoleApplicationTestTests.h"
#include <boost/filesystem/operations.hpp>

using namespace Ishiko::TestFramework;
using namespace boost::filesystem;

void AddConsoleApplicationTestTests(TestHarness& theTestHarness)
{
    TestSequence& testSequence = theTestHarness.appendTestSequence("ConsoleApplicationTest tests");

    testSequence.append<HeapAllocationErrorsTest>("Creation test 1", ConsoleApplicationTestCreationTest1);
    testSequence.append<HeapAllocationErrorsTest>("run success test 1", ConsoleApplicationTestRunSuccessTest1);
    testSequence.append<HeapAllocationErrorsTest>("run success test 2", ConsoleApplicationTestRunSuccessTest2);
    testSequence.append<HeapAllocationErrorsTest>("run failure test 1", ConsoleApplicationTestRunFailureTest1);
    testSequence.append<HeapAllocationErrorsTest>("run success test 3", ConsoleApplicationTestRunSuccessTest3);
    testSequence.append<HeapAllocationErrorsTest>("run failure test 2", ConsoleApplicationTestRunFailureTest2);
}

TestResult::EOutcome ConsoleApplicationTestCreationTest1(Test& test)
{
    path executablePath(test.environment().getTestDataDirectory() / "Binaries/WriteFileTestHelper.exe");

    ConsoleApplicationTest applicationTest(TestNumber(), "ConsoleApplicationTestCreationTest1",
        executablePath.string().c_str(), 0);

    return TestResult::ePassed;
}

TestResult::EOutcome ConsoleApplicationTestRunSuccessTest1(Test& test)
{
    path executablePath(test.environment().getTestDataDirectory() / "Binaries/ExitCodeTestHelper.exe");

    ConsoleApplicationTest applicationTest(TestNumber(), "ConsoleApplicationTestRunSuccessTest1",
        executablePath.string(), 0);
    applicationTest.run();

    if (applicationTest.result().passed())
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome ConsoleApplicationTestRunSuccessTest2(Test& test)
{
    path executablePath(test.environment().getTestDataDirectory() / "Binaries/ExitCodeTestHelper.exe");

    std::string commandLine = executablePath.string() + " 3";
    ConsoleApplicationTest applicationTest(TestNumber(), "ConsoleApplicationTestRunSuccessTest2", commandLine, 3);
    applicationTest.run();

    if (applicationTest.result().passed())
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome ConsoleApplicationTestRunFailureTest1(Test& test)
{
    path executablePath(test.environment().getTestDataDirectory() / "Binaries/ExitCodeTestHelper.exe");

    ConsoleApplicationTest applicationTest(TestNumber(), "ConsoleApplicationTestRunFailureTest1",
        executablePath.string(), 3);
    applicationTest.run();

    if (applicationTest.result().passed())
    {
        return TestResult::eFailed;
    }
    else
    {
        return TestResult::ePassed;
    }
}

TestResult::EOutcome ConsoleApplicationTestRunSuccessTest3(Test& test)
{
    create_directories(test.environment().getTestOutputDirectory() / "ConsoleApplicationTestTests");

    path executablePath(test.environment().getTestDataDirectory() / "Binaries/StandardOutputTestHelper.exe");
    path outputPath(test.environment().getTestOutputDirectory()
        / "ConsoleApplicationTestTests/ConsoleApplicationTestRunSuccessTest3.txt");
    remove(outputPath);
    path referencePath(test.environment().getReferenceDataDirectory()
        / "ConsoleApplicationTestTests/ConsoleApplicationTestRunSuccessTest3.txt");

    ConsoleApplicationTest applicationTest(TestNumber(), "ConsoleApplicationTestRunSuccessTest3",
        executablePath.string().c_str(), 0);
    applicationTest.setStandardOutputFilePath(outputPath);
    applicationTest.setStandardOutputReferenceFilePath(referencePath);
    applicationTest.run();

    if (applicationTest.result().passed())
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome ConsoleApplicationTestRunFailureTest2(Test& test)
{
    path executablePath(test.environment().getTestDataDirectory() / "Binaries/StandardOutputTestHelper.exe");
    path outputPath(test.environment().getTestOutputDirectory()
        / "ConsoleApplicationTestTests/ConsoleApplicationTestRunFailureTest2.txt");
    remove(outputPath);
    path referencePath(test.environment().getReferenceDataDirectory()
        / "ConsoleApplicationTestTests/ConsoleApplicationTestRunFailureTest2.txt");

    ConsoleApplicationTest applicationTest(TestNumber(), "ConsoleApplicationTestRunFailureTest2",
        executablePath.string().c_str(), 0);
    applicationTest.setStandardOutputFilePath(outputPath);
    applicationTest.setStandardOutputReferenceFilePath(referencePath);
    applicationTest.run();

    if (applicationTest.result().passed())
    {
        return TestResult::eFailed;
    }
    else
    {
        return TestResult::ePassed;
    }
}
