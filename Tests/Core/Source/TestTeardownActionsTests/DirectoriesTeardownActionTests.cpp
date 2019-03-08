/*
    Copyright (c) 2015-2019 Xavier Leclercq

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

#include "DirectoriesTeardownActionTests.h"
#include "Ishiko/TestFramework/Core/DebugHeap.h"
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

    const char* path = "../../TestOutput/TestTeardownActionsTests/DirectoriesTeardownActionTeardownTest1";
    std::shared_ptr<DirectoriesTeardownAction> action = std::make_shared<DirectoriesTeardownAction>();
    action->add(path);
    test.addTeardownAction(action);

    tracking.restore();

    if (create_directories(path))
    {
        ISHTF_PASS();
    }
}

void DirectoriesTeardownActionTests::TeardownTest1(Test& test)
{
    const char* path = "../../TestOutput/TestTeardownActionsTests/DirectoriesTeardownActionTeardownTest1";

    Test functionTest(TestNumber(), "DirectoriesTeardownActionTeardownTest1",
        DirectoriesTeardownActionTeardownTest1Helper);
    functionTest.run();

    ISHTF_FAIL_IF(exists(path));
    ISHTF_FAIL_IF(!functionTest.passed());
    ISHTF_PASS();
}
