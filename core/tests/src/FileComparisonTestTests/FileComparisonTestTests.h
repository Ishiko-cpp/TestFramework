/*
    Copyright (c) 2007-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_TESTS_CORE_FILECOMPARISONTESTTESTS_FILECOMPARISONTESTTESTS_H_
#define _ISHIKO_TESTS_TESTS_CORE_FILECOMPARISONTESTTESTS_FILECOMPARISONTESTTESTS_H_

#include <Ishiko/TestFramework/Core.hpp>

class FileComparisonTestTests : public Ishiko::TestSequence
{
public:
    FileComparisonTestTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void CreationTest1(Ishiko::Test& test);
    static void RunSuccessTest1(Ishiko::Test& test);
    static void RunFailureTest1(Ishiko::Test& test);
};

#endif
