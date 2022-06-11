/*
    Copyright (c) 2016-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "ProcessActionTests.h"
#include <Ishiko/TestFramework/Core/ProcessAction.hpp>
#include <boost/filesystem/operations.hpp>

using namespace Ishiko;

ProcessActionTests::ProcessActionTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "ProcessAction tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("setup (failure) test 1", SetupFailureTest1);
    append<HeapAllocationErrorsTest>("setup() (wait for exit) test 1", SetupWaitForExitTest1);
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

void ProcessActionTests::SetupWaitForExitTest1(Test& test)
{
#ifdef __linux__
    boost::filesystem::path executablePath(test.context().getDataDirectory() / "bin/WriteFileTestHelper");
#else
    boost::filesystem::path executablePath(test.context().getDataDirectory() / "bin/WriteFileTestHelper.exe");
#endif
    boost::filesystem::path outputPath =
        test.context().getOutputPath("TestSetupActionsTests/ProcessActionSetupTest1.txt");
    create_directories(test.context().getOutputDirectory() / "TestSetupActionsTests");

    ProcessAction action(executablePath.string() + " " + outputPath.string(), ProcessAction::eWaitForExit);
    action.setup();
    action.teardown();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("TestSetupActionsTests/ProcessActionSetupTest1.txt");
    ISHIKO_TEST_PASS();
}

void ProcessActionTests::SetupTerminateTest1(Test& test)
{
#ifdef __linux__
    boost::filesystem::path executablePath(test.context().getDataDirectory() / "bin/PermanentAppTestHelper");
#else
    boost::filesystem::path executablePath(test.context().getDataDirectory() / "bin/PermanentAppTestHelper.exe");
#endif

    ProcessAction action(executablePath.string(), ProcessAction::eTerminate);
    action.setup();
    action.teardown();

    ISHIKO_TEST_PASS();
}
