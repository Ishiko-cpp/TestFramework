/*
    Copyright (c) 2015-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "FilesTeardownActionTests.h"
#include "Ishiko/Tests/Core/DebugHeap.h"
#include <boost/filesystem.hpp>

using namespace Ishiko::Tests;
using namespace boost::filesystem;

FilesTeardownActionTests::FilesTeardownActionTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "FilesTeardownAction tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("teardown() test 1", TeardownTest1);
}

void FilesTeardownActionTests::CreationTest1(Test& test)
{
    FilesTeardownAction action;
    ISHTF_PASS();
}

void FilesTeardownActionTeardownTest1Helper(Test& test)
{
    DebugHeap::TrackingState tracking;
    tracking.disableTracking();

    path filePath(test.environment().getTestOutputDirectory()
        / "TestTeardownActionsTests/FilesTeardownActionTeardownTest1");
    std::shared_ptr<FilesTeardownAction> action = std::make_shared<FilesTeardownAction>();
    action->add(filePath);
    test.addTeardownAction(action);

    tracking.restore();

    std::ofstream file(filePath.string());
    file.close();

    ISHTF_FAIL_IF_NOT(exists(filePath));
    ISHTF_PASS();
}

void FilesTeardownActionTests::TeardownTest1(Test& test)
{
    path filePath(test.environment().getTestOutputDirectory()
        / "TestTeardownActionsTests/FilesTeardownActionTeardownTest1");

    Test teardownTest(TestNumber(), "FilesTeardownActionTeardownTest1", FilesTeardownActionTeardownTest1Helper,
        test.environment());
    teardownTest.run();

    ISHTF_FAIL_IF(exists(filePath));
    ISHTF_FAIL_IF_NOT(teardownTest.passed());
    ISHTF_PASS();
}
