/*
    Copyright (c) 2015-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_TESTS_CORE_TESTTEARDOWNACTIONSTESTS_TESTTEARDOWNACTIONSTESTS_H_
#define _ISHIKO_TESTS_TESTS_CORE_TESTTEARDOWNACTIONSTESTS_TESTTEARDOWNACTIONSTESTS_H_

#include <Ishiko/TestFramework/Core.hpp>

class TestTeardownActionsTests : public Ishiko::TestSequence
{
public:
    TestTeardownActionsTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);
};

#endif
