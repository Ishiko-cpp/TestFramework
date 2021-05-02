/*
    Copyright (c) 20121 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_TEST_TESTFRAMEWORK_CORE_TESTMACROSFORMATTERTESTS_H_
#define _ISHIKO_TEST_TESTFRAMEWORK_CORE_TESTMACROSFORMATTERTESTS_H_

#include "Ishiko/TestFramework/TestFrameworkCore.h"

class TestMacrosFormatterTests : public Ishiko::Tests::TestSequence
{
public:
    TestMacrosFormatterTests(const Ishiko::Tests::TestNumber& number,
        const Ishiko::Tests::TestEnvironment& environment);
};

#endif
