/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#include "TestMacrosFormatterTests.h"
#include "Ishiko/TestFramework/Core/TestMacrosFormatter.h"

using namespace Ishiko::Tests;

TestMacrosFormatterTests::TestMacrosFormatterTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "TestMacrosFormatter tests", environment)
{
    append<HeapAllocationErrorsTest>("FormatComparison test 1", FormatComparisonTest1);
    append<HeapAllocationErrorsTest>("FormatComparison test 2", FormatComparisonTest2);
    append<HeapAllocationErrorsTest>("FormatComparison test 3", FormatComparisonTest3);
    append<HeapAllocationErrorsTest>("FormatComparison test 4", FormatComparisonTest4);
    append<HeapAllocationErrorsTest>("FormatComparison test 5", FormatComparisonTest5);
}

void TestMacrosFormatterTests::FormatComparisonTest1(Test& test)
{
    std::string value = "value";
    std::string reference = "reference";
    std::string output = TestMacrosFormatter::FormatComparison(value, reference);

    ISHTF_FAIL_IF_NEQ(output, "value != reference");
    ISHTF_PASS();
}

void TestMacrosFormatterTests::FormatComparisonTest2(Test& test)
{
    const char value[] = "value";
    const char reference[] = "reference";
    std::string output = TestMacrosFormatter::FormatComparison(value, reference);

    ISHTF_FAIL_IF_NEQ(output, "value != reference");
    ISHTF_PASS();
}

void TestMacrosFormatterTests::FormatComparisonTest3(Test& test)
{
    bool value = false;
    bool reference = true;
    std::string output = TestMacrosFormatter::FormatComparison(value, reference);

    ISHTF_FAIL_IF_NEQ(output, "false != true");
    ISHTF_PASS();
}

void TestMacrosFormatterTests::FormatComparisonTest4(Test& test)
{
    int value = 5;
    int reference = 7;
    std::string output = TestMacrosFormatter::FormatComparison(value, reference);

    ISHTF_FAIL_IF_NEQ(output, "5 != 7");
    ISHTF_PASS();
}

enum FormatComparisonTest5Helper
{
    value1 = 1,
    value2 = 5
};

void TestMacrosFormatterTests::FormatComparisonTest5(Test& test)
{
    FormatComparisonTest5Helper value = FormatComparisonTest5Helper::value1;
    FormatComparisonTest5Helper reference = FormatComparisonTest5Helper::value2;
    std::string output = TestMacrosFormatter::FormatComparison(value, reference);

    ISHTF_FAIL_IF_NEQ(output, "1 != 5");
    ISHTF_PASS();
}
