/*
    Copyright (c) 2007-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_TESTS_CORE_FILECOMPARISONTESTTESTS_FILECOMPARISONTESTTESTS_H_
#define _ISHIKO_TESTS_TESTS_CORE_FILECOMPARISONTESTTESTS_FILECOMPARISONTESTTESTS_H_

#include <Ishiko/Tests/Core.hpp>

class FileComparisonTestTests : public Ishiko::Tests::TestSequence
{
public:
    FileComparisonTestTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestContext& context);

private:
    static void CreationTest1(Ishiko::Tests::Test& test);
    static void RunSuccessTest1(Ishiko::Tests::Test& test);
    static void RunFailureTest1(Ishiko::Tests::Test& test);
};

#endif
