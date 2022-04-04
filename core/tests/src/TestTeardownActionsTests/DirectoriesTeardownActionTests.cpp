/*
    Copyright (c) 2015-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "DirectoriesTeardownActionTests.h"
#include <boost/filesystem.hpp>
#include <Ishiko/TestFramework/Core/DebugHeap.hpp>

using namespace Ishiko;
using namespace boost::filesystem;

DirectoriesTeardownActionTests::DirectoriesTeardownActionTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "DirectoriesTeardownAction tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("teardown() test 1", TeardownTest1);
}

void DirectoriesTeardownActionTests::CreationTest1(Test& test)
{
    DirectoriesTeardownAction action;

    ISHIKO_TEST_PASS();
}

void DirectoriesTeardownActionTeardownTest1Helper(Test& test)
{
    DebugHeap::TrackingState tracking;
    tracking.disableTracking();

    path directoryPath(
        test.context().getTestOutputPath("TestTeardownActionsTests/DirectoriesTeardownActionTeardownTest1"));
    std::shared_ptr<DirectoriesTeardownAction> action = std::make_shared<DirectoriesTeardownAction>();
    action->add(directoryPath);
    test.addTeardownAction(action);

    tracking.restore();

    if (create_directories(directoryPath))
    {
        ISHIKO_TEST_PASS();
    }
}

void DirectoriesTeardownActionTests::TeardownTest1(Test& test)
{
    path directoryPath(
        test.context().getTestOutputPath("TestTeardownActionsTests/DirectoriesTeardownActionTeardownTest1"));

    Test functionTest(TestNumber(), "DirectoriesTeardownActionTeardownTest1",
        DirectoriesTeardownActionTeardownTest1Helper, test.context());
    functionTest.run();

    ISHIKO_TEST_FAIL_IF(exists(directoryPath));
    ISHIKO_TEST_FAIL_IF_NOT(functionTest.passed());
    ISHIKO_TEST_PASS();
}
