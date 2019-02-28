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

#include "TestHarnessTests.h"
#include "Ishiko/TestFramework/Core/TestHarness.h"

void TestHarnessTests::AddTests(Ishiko::TestFramework::TestHarness& theTestHarness)
{
    Ishiko::TestFramework::TestSequence& testHarnessTestSequence =
        theTestHarness.appendTestSequence("TestHarness tests");

    new Ishiko::TestFramework::HeapAllocationErrorsTest("Creation test 1", CreationTest1, testHarnessTestSequence);
    new Ishiko::TestFramework::HeapAllocationErrorsTest("run test 1", RunTest1, testHarnessTestSequence);
}

Ishiko::TestFramework::TestResult::EOutcome TestHarnessTests::CreationTest1()
{
    Ishiko::TestFramework::TestHarness theTestHarness("TestHarnessTests_CreationTest1");
    return Ishiko::TestFramework::TestResult::ePassed;
}

Ishiko::TestFramework::TestResult::EOutcome TestHarnessTests::RunTest1()
{
    Ishiko::TestFramework::TestResult::EOutcome result = Ishiko::TestFramework::TestResult::eFailed;

    Ishiko::TestFramework::TestHarness theTestHarness("TestHarnessTests_RunTest1");
    int returnCode = theTestHarness.run();
    if (returnCode == Ishiko::TestFramework::eTestFailure)
    {
        result = Ishiko::TestFramework::TestResult::ePassed;
    }

    return result;
}
