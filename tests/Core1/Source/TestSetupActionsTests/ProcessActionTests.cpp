/*
    Copyright (c) 2016-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "ProcessActionTests.h"
#include "Ishiko/Tests/Core/ProcessAction.h"
#include <boost/filesystem/operations.hpp>

using namespace Ishiko::Tests;
using namespace boost::filesystem;

ProcessActionTests::ProcessActionTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "ProcessAction tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("setup (failure) test 1", SetupFailureTest1);
    append<FileComparisonTest>("setup() (wait for exit) test 1", SetupWaitForExitTest1);
    append<HeapAllocationErrorsTest>("setup() (terminate) test 1", SetupTerminateTest1);
}

void ProcessActionTests::CreationTest1(Test& test)
{
    ProcessAction action("../../TestData/Bin/WriteFileTestHelper.exe", ProcessAction::eWaitForExit);
    ISHTF_PASS();
}

void ProcessActionTests::SetupFailureTest1(Test& test)
{
    ProcessAction action("doesnotexist", ProcessAction::eWaitForExit);

    try
    {
        action.setup();
        action.teardown();
    }
    catch (...)
    {
        ISHTF_PASS();
    }
}

void ProcessActionTests::SetupWaitForExitTest1(FileComparisonTest& test)
{
#ifdef __linux__
    path executablePath(test.environment().getTestDataDirectory() / "Bin/WriteFileTestHelper");
#else
    path executablePath(test.environment().getTestDataDirectory() / "Bin/WriteFileTestHelper.exe");
#endif
    path outputPath(test.environment().getTestOutputDirectory() / "TestSetupActionsTests/ProcessActionSetupTest1.txt");
    test.setOutputFilePath(outputPath);
    create_directories(test.environment().getTestOutputDirectory() / "TestSetupActionsTests");
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "TestSetupActionsTests/ProcessActionSetupTest1.txt");

    ProcessAction action(executablePath.string() + " " + outputPath.string(), ProcessAction::eWaitForExit);
    action.setup();
    action.teardown();

    ISHTF_PASS();
}

void ProcessActionTests::SetupTerminateTest1(Test& test)
{
#ifdef __linux__
    path executablePath(test.environment().getTestDataDirectory() / "Bin/PermanentAppTestHelper");
#else
    path executablePath(test.environment().getTestDataDirectory() / "Bin/PermanentAppTestHelper.exe");
#endif

    ProcessAction action(executablePath.string(), ProcessAction::eTerminate);
    action.setup();
    action.teardown();

    ISHTF_PASS();
}
