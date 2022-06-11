/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTS_JUNITXMLWRITERTESTS_HPP_
#define _ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTS_JUNITXMLWRITERTESTS_HPP_

#include <Ishiko/TestFramework/Core.hpp>

class JUnitXMLWriterTests : public Ishiko::TestSequence
{
public:
    JUnitXMLWriterTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void CreateTest1(Ishiko::Test& test);
    static void WriteTestSuitesStartTest1(Ishiko::Test& test);
    static void WriteTestSuiteStartTest1(Ishiko::Test& test);
    static void WriteTestCaseStartTest1(Ishiko::Test& test);
};

#endif
