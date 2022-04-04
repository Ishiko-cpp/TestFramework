/*
    Copyright (c) 2016-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "ProcessActionTests.h"
#include <Ishiko/TestFramework/Core/ProcessAction.hpp>
#include <boost/filesystem/operations.hpp>

using namespace Ishiko;
using namespace boost::filesystem;

ProcessActionTests::ProcessActionTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "ProcessAction tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("setup (failure) test 1", SetupFailureTest1);
    append<FileComparisonTest>("setup() (wait for exit) test 1", SetupWaitForExitTest1);
    append<HeapAllocationErrorsTest>("setup() (terminate) test 1", SetupTerminateTest1);
}

void ProcessActionTests::CreationTest1(Test& test)
{
    ProcessAction action("../../data/bin/WriteFileTestHelper.exe", ProcessAction::eWaitForExit);
    ISHIKO_TEST_PASS();
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
        ISHIKO_TEST_PASS();
    }
}

void ProcessActionTests::SetupWaitForExitTest1(FileComparisonTest& test)
{
#ifdef __linux__
    path executablePath(test.context().getTestDataDirectory() / "bin/WriteFileTestHelper");
#else
    path executablePath(test.context().getTestDataDirectory() / "bin/WriteFileTestHelper.exe");
#endif
    path outputPath(test.context().getTestOutputDirectory() / "TestSetupActionsTests/ProcessActionSetupTest1.txt");
    test.setOutputFilePath(outputPath);
    create_directories(test.context().getTestOutputDirectory() / "TestSetupActionsTests");
    test.setReferenceFilePath(
        test.context().getReferenceDataPath("TestSetupActionsTests/ProcessActionSetupTest1.txt"));

    ProcessAction action(executablePath.string() + " " + outputPath.string(), ProcessAction::eWaitForExit);
    action.setup();
    action.teardown();

    ISHIKO_TEST_PASS();
}

void ProcessActionTests::SetupTerminateTest1(Test& test)
{
#ifdef __linux__
    path executablePath(test.context().getTestDataDirectory() / "bin/PermanentAppTestHelper");
#else
    path executablePath(test.context().getTestDataDirectory() / "bin/PermanentAppTestHelper.exe");
#endif

    ProcessAction action(executablePath.string(), ProcessAction::eTerminate);
    action.setup();
    action.teardown();

    ISHIKO_TEST_PASS();
}
