/*
    Copyright (c) 2007-2019 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_TEST_TESTFRAMEWORK_CORE_FILECOMPARISONTESTTESTS_FILECOMPARISONTESTTESTS_H_
#define _ISHIKO_TEST_TESTFRAMEWORK_CORE_FILECOMPARISONTESTTESTS_FILECOMPARISONTESTTESTS_H_

#include "Ishiko/TestFramework/TestFrameworkCore.h"

class FileComparisonTestTests : public Ishiko::Tests::TestSequence
{
public:
    FileComparisonTestTests(const Ishiko::Tests::TestNumber& number,
        const Ishiko::Tests::TestEnvironment& environment);

private:
    static void CreationTest1(Ishiko::Tests::Test& test);
    static void RunSuccessTest1(Ishiko::Tests::Test& test);
    static void RunFailureTest1(Ishiko::Tests::Test& test);
};

#endif
