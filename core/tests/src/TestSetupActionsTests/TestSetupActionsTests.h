/*
    Copyright (c) 2016-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_TESTS_CORE_TESTSETUPACTIONSTESTS_TESTSETUPACTIONSTESTS_H_
#define _ISHIKO_TESTS_TESTS_CORE_TESTSETUPACTIONSTESTS_TESTSETUPACTIONSTESTS_H_

#include <Ishiko/TestFramework/Core.hpp>

class TestSetupActionsTests : public Ishiko::TestSequence
{
public:
    TestSetupActionsTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);
};

#endif
