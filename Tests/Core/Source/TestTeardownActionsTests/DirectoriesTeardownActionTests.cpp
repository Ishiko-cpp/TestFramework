/*
    Copyright (c) 2015-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "DirectoriesTeardownActionTests.h"
#include "Ishiko/Tests/Core/DebugHeap.h"
#include <boost/filesystem.hpp>

using namespace Ishiko::Tests;
using namespace boost::filesystem;

DirectoriesTeardownActionTests::DirectoriesTeardownActionTests(const TestNumber& number,
    const TestEnvironment& environment)
    : TestSequence(number, "DirectoriesTeardownAction tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("teardown() test 1", TeardownTest1);
}

void DirectoriesTeardownActionTests::CreationTest1(Test& test)
{
    DirectoriesTeardownAction action;
    ISHTF_PASS();
}

void DirectoriesTeardownActionTeardownTest1Helper(Test& test)
{
    DebugHeap::TrackingState tracking;
    tracking.disableTracking();

    path directoryPath(test.environment().getTestOutputDirectory()
        / "TestTeardownActionsTests/DirectoriesTeardownActionTeardownTest1");
    std::shared_ptr<DirectoriesTeardownAction> action = std::make_shared<DirectoriesTeardownAction>();
    action->add(directoryPath);
    test.addTeardownAction(action);

    tracking.restore();

    if (create_directories(directoryPath))
    {
        ISHTF_PASS();
    }
}

void DirectoriesTeardownActionTests::TeardownTest1(Test& test)
{
    path directoryPath(test.environment().getTestOutputDirectory()
        / "TestTeardownActionsTests/DirectoriesTeardownActionTeardownTest1");

    Test functionTest(TestNumber(), "DirectoriesTeardownActionTeardownTest1",
        DirectoriesTeardownActionTeardownTest1Helper, test.environment());
    functionTest.run();

    ISHTF_FAIL_IF(exists(directoryPath));
    ISHTF_FAIL_IF_NOT(functionTest.passed());
    ISHTF_PASS();
}
