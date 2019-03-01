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

#include "ProcessActionTests.h"
#include "Ishiko/TestFramework/Core/ProcessAction.h"
#include <boost/filesystem/operations.hpp>

void AddProcessActionTests(Ishiko::TestFramework::TestSequence& testSequence)
{
    Ishiko::TestFramework::TestSequence& processActionTestSequence = 
        testSequence.append<Ishiko::TestFramework::TestSequence>("ProcessAction tests");

    new Ishiko::TestFramework::HeapAllocationErrorsTest("Creation test 1",
        ProcessActionCreationTest1, processActionTestSequence);
    processActionTestSequence.append<Ishiko::TestFramework::FileComparisonTest>("setup() (wait for exit) test 1",
        ProcessActionSetupWaitForExitTest1);
    new Ishiko::TestFramework::HeapAllocationErrorsTest("setup() (terminate) test 2",
        ProcessActionSetupTerminateTest1, processActionTestSequence);
}

Ishiko::TestFramework::TestResult::EOutcome ProcessActionCreationTest1()
{
    Ishiko::TestFramework::ProcessAction action(
        "../../TestData/Binaries/WriteFileTestHelper.exe", 
        Ishiko::TestFramework::ProcessAction::eWaitForExit
        );
    return Ishiko::TestFramework::TestResult::ePassed;
}

Ishiko::TestFramework::TestResult::EOutcome ProcessActionSetupWaitForExitTest1(Ishiko::TestFramework::FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "TestSetupActionsTests/ProcessActionSetupTest1.txt");
    test.setOutputFilePath(outputPath);
    boost::filesystem::create_directories(test.environment().getTestOutputDirectory() / "TestSetupActionsTests");
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "TestSetupActionsTests/ProcessActionSetupTest1.txt");

    Ishiko::TestFramework::ProcessAction action(
        "../../TestData/Binaries/WriteFileTestHelper.exe " + outputPath.generic_string(),
        Ishiko::TestFramework::ProcessAction::eWaitForExit
        );
    action.setup();
    action.teardown();
    return Ishiko::TestFramework::TestResult::ePassed;
}

Ishiko::TestFramework::TestResult::EOutcome ProcessActionSetupTerminateTest1()
{
    Ishiko::TestFramework::ProcessAction action(
        "../../TestData/Binaries/PermanentAppTestHelper.exe",
        Ishiko::TestFramework::ProcessAction::eTerminate
        );
    action.setup();
    action.teardown();
    return Ishiko::TestFramework::TestResult::ePassed;
}
