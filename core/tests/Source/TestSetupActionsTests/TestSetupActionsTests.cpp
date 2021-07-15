/*
    Copyright (c) 2016-2019 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "TestSetupActionsTests.h"
#include "ProcessActionTests.h"

using namespace Ishiko::Tests;

TestSetupActionsTests::TestSetupActionsTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "TestSetupAction tests", environment)
{
    append<ProcessActionTests>();
}
