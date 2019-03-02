/*
    Copyright (c) 2007-2019 Xavier Leclercq

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

#include "TestEnvironmentTests.h"
#include "Ishiko/Process/Environment.h"

using namespace Ishiko::TestFramework;

void AddTestEnvironmentTests(TestHarness& theTestHarness)
{
    TestSequence& testSequence = theTestHarness.appendTestSequence("TestEnvironment tests");

    testSequence.append<HeapAllocationErrorsTest>("Creation test 1", TestEnvironmentCreationTest1);
    testSequence.append<HeapAllocationErrorsTest>("getTestDataDirectory test 1",
        TestEnvironmentGetTestDataDirectoryTest1);
    testSequence.append<HeapAllocationErrorsTest>("getTestDataDirectory test 2",
        TestEnvironmentGetTestDataDirectoryTest2);
    testSequence.append<HeapAllocationErrorsTest>("getTestDataDirectory test 3",
        TestEnvironmentGetTestDataDirectoryTest3);
}

TestResult::EOutcome TestEnvironmentCreationTest1()
{
    TestEnvironment environment;
    return TestResult::ePassed;
}

TestResult::EOutcome TestEnvironmentGetTestDataDirectoryTest1()
{
    TestResult::EOutcome result = TestResult::eFailed;
    try
    {
        TestEnvironment environment;
        environment.getTestDataDirectory("dummy");
    }
    catch (const TestException& exception)
    {
        result = TestResult::ePassed;
    }
    return result;
}

TestResult::EOutcome TestEnvironmentGetTestDataDirectoryTest2()
{
    TestEnvironment environment;
    environment.setTestDataDirectory("id1", "path1");
    if (environment.getTestDataDirectory("id1") == "path1")
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome TestEnvironmentGetTestDataDirectoryTest3()
{
    Ishiko::Process::Environment::set("TestEnvironmentGetTestDataDirectoryTest3", "dummy");

    TestEnvironment environment;
    environment.setTestDataDirectory("id1", "$(TestEnvironmentGetTestDataDirectoryTest3)/path1");
    if (environment.getTestDataDirectory("id1") == "dummy/path1")
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}
