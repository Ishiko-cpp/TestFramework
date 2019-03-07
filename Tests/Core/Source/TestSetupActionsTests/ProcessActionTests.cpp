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

using namespace Ishiko::Tests;
using namespace boost::filesystem;

ProcessActionTests::ProcessActionTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "ProcessAction tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<FileComparisonTest>("setup() (wait for exit) test 1", SetupWaitForExitTest1);
    append<HeapAllocationErrorsTest>("setup() (terminate) test 2", SetupTerminateTest1);
}

void ProcessActionTests::CreationTest1(Test& test)
{
    ProcessAction action("../../TestData/Binaries/WriteFileTestHelper.exe", ProcessAction::eWaitForExit);
    ISHTF_PASS();
}

void ProcessActionTests::SetupWaitForExitTest1(FileComparisonTest& test)
{
    path outputPath(test.environment().getTestOutputDirectory() / "TestSetupActionsTests/ProcessActionSetupTest1.txt");
    test.setOutputFilePath(outputPath);
    create_directories(test.environment().getTestOutputDirectory() / "TestSetupActionsTests");
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "TestSetupActionsTests/ProcessActionSetupTest1.txt");

    ProcessAction action("../../TestData/Binaries/WriteFileTestHelper.exe " + outputPath.generic_string(),
        ProcessAction::eWaitForExit);
    action.setup();
    action.teardown();

    ISHTF_PASS();
}

void ProcessActionTests::SetupTerminateTest1(Test& test)
{
    ProcessAction action("../../TestData/Binaries/PermanentAppTestHelper.exe", ProcessAction::eTerminate);
    action.setup();
    action.teardown();

    ISHTF_PASS();
}
