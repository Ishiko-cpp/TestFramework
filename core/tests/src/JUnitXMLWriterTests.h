/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_TESTS_CORE_JUNITXMLWRITERTESTS_H_
#define _ISHIKO_TESTS_TESTS_CORE_JUNITXMLWRITERTESTS_H_

#include <Ishiko/TestFramework/Core.hpp>

class JUnitXMLWriterTests : public Ishiko::TestSequence
{
public:
    JUnitXMLWriterTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
};

#endif
