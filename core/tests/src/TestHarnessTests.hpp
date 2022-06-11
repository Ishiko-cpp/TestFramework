/*
    Copyright (c) 2007-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTS_TESTHARNESSTESTS_HPP_
#define _ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTS_TESTHARNESSTESTS_HPP_

#include <Ishiko/TestFramework/Core.hpp>

class TestHarnessTests : public Ishiko::TestSequence
{
public:
    TestHarnessTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void CreationTest1(Ishiko::Test& test);
    static void RunTest1(Ishiko::Test& test);
    static void RunTest2(Ishiko::Test& test);
    static void RunTest3(Ishiko::Test& test);
    static void JUnitXMLReportTest1(Ishiko::Test& test);
    static void JUnitXMLReportTest2(Ishiko::Test& test);
    static void JUnitXMLReportTest3(Ishiko::Test& test);
};

#endif
