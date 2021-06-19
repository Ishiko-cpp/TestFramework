/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_TESTFRAMEWORK_TESTS_CORE_JUNITXMLFILETESTS_H_
#define _ISHIKO_TESTFRAMEWORK_TESTS_CORE_JUNITXMLFILETESTS_H_

#include "Ishiko/TestFramework/TestFrameworkCore.h"

class JUnitXMLFileTests : public Ishiko::Tests::TestSequence
{
public:
    JUnitXMLFileTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
};

#endif
