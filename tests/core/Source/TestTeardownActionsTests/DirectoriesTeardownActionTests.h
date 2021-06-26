/*
    Copyright (c) 2015-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_TESTS_CORE_TESTTEARDOWNACTIONSTESTS_DIRECTORIESTEARDOWNACTIONTESTS_H_
#define _ISHIKO_TESTS_TESTS_CORE_TESTTEARDOWNACTIONSTESTS_DIRECTORIESTEARDOWNACTIONTESTS_H_

#include <Ishiko/Tests/Core.h>

class DirectoriesTeardownActionTests : public Ishiko::Tests::TestSequence
{
public:
    DirectoriesTeardownActionTests(const Ishiko::Tests::TestNumber& number,
        const Ishiko::Tests::TestEnvironment& environment);

private:
    static void CreationTest1(Ishiko::Tests::Test& test);
    static void TeardownTest1(Ishiko::Tests::Test& test);
};

#endif
