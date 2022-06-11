/*
    Copyright (c) 2015-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "TestTeardownActionsTests.h"
#include "DirectoriesTeardownActionTests.h"
#include "FilesTeardownActionTests.h"

using namespace Ishiko;

TestTeardownActionsTests::TestTeardownActionsTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "TestTeardownAction tests", context)
{
    append<DirectoriesTeardownActionTests>();
    append<FilesTeardownActionTests>();
}
