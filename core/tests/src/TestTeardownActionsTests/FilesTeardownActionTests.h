/*
    Copyright (c) 2015-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_TESTS_CORE_TESTTEARDOWNACTIONSTESTS_FILESTEARDOWNACTIONTESTS_H_
#define _ISHIKO_TESTS_TESTS_CORE_TESTTEARDOWNACTIONSTESTS_FILESTEARDOWNACTIONTESTS_H_

#include <Ishiko/Tests/Core.hpp>

class FilesTeardownActionTests : public Ishiko::TestSequence
{
public:
    FilesTeardownActionTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void CreationTest1(Ishiko::Test& test);
    static void TeardownTest1(Ishiko::Test& test);
};

#endif
