/*
    Copyright (c) 2016-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "TestSetupActionsTests.h"
#include "ProcessActionTests.h"

using namespace Ishiko;

TestSetupActionsTests::TestSetupActionsTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "TestSetupAction tests", context)
{
    append<ProcessActionTests>();
}
