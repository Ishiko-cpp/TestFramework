/*
    Copyright (c) 2015-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "FilesTeardownActionTests.h"
#include <boost/filesystem.hpp>
#include <Ishiko/TestFramework/Core/DebugHeap.hpp>

using namespace Ishiko;
using namespace boost::filesystem;

FilesTeardownActionTests::FilesTeardownActionTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "FilesTeardownAction tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("teardown() test 1", TeardownTest1);
}

void FilesTeardownActionTests::CreationTest1(Test& test)
{
    FilesTeardownAction action;

    ISHIKO_TEST_PASS();
}

void FilesTeardownActionTeardownTest1Helper(Test& test)
{
    DebugHeap::TrackingState tracking;
    tracking.disableTracking();

    path filePath(test.context().getTestOutputPath("TestTeardownActionsTests/FilesTeardownActionTeardownTest1"));
    std::shared_ptr<FilesTeardownAction> action = std::make_shared<FilesTeardownAction>();
    action->add(filePath);
    test.addTeardownAction(action);

    tracking.restore();

    std::ofstream file(filePath.string());
    file.close();

    ISHIKO_TEST_FAIL_IF_NOT(exists(filePath));
    ISHIKO_TEST_PASS();
}

void FilesTeardownActionTests::TeardownTest1(Test& test)
{
    path filePath(test.context().getTestOutputPath("TestTeardownActionsTests/FilesTeardownActionTeardownTest1"));

    Test teardownTest(TestNumber(), "FilesTeardownActionTeardownTest1", FilesTeardownActionTeardownTest1Helper,
        test.context());
    teardownTest.run();

    ISHIKO_TEST_FAIL_IF(exists(filePath));
    ISHIKO_TEST_FAIL_IF_NOT(teardownTest.passed());
    ISHIKO_TEST_PASS();
}
