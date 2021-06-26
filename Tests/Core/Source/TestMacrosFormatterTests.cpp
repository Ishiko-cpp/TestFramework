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
    append<HeapAllocationErrorsTest>("Format test 1", FormatTest1);
    append<HeapAllocationErrorsTest>("Format test 2", FormatTest2);
    append<HeapAllocationErrorsTest>("Format test 3", FormatTest3);
    append<HeapAllocationErrorsTest>("Format test 4", FormatTest4);
    append<HeapAllocationErrorsTest>("Format test 5", FormatTest5);
    append<HeapAllocationErrorsTest>("Format test 6", FormatTest6);
}

void TestMacrosFormatterTests::FormatTest1(Test& test)
{
    std::string value = "value";
    std::string output = TestMacrosFormatter::Format("ISHTF_FAIL_IF", "value", value);

    ISHTF_FAIL_IF_NEQ(output, "ISHTF_FAIL_IF(value) failed with actual value (value)");
    ISHTF_PASS();
}


void TestMacrosFormatterTests::FormatTest2(Test& test)
{
    std::string value = "value";
    std::string reference = "reference";
    std::string output = TestMacrosFormatter::Format("ISHTF_FAIL_IF_EQ", "value", "reference", value, reference);

    ISHTF_FAIL_IF_NEQ(output, "ISHTF_FAIL_IF_EQ(value, reference) failed with actual values (value, reference)");
    ISHTF_PASS();
}

void TestMacrosFormatterTests::FormatTest3(Test& test)
{
    const char value[] = "value";
    const char reference[] = "reference";
    std::string output = TestMacrosFormatter::Format("ISHTF_FAIL_IF_EQ", "value", "reference", value, reference);

    ISHTF_FAIL_IF_NEQ(output, "ISHTF_FAIL_IF_EQ(value, reference) failed with actual values (value, reference)");
    ISHTF_PASS();
}

void TestMacrosFormatterTests::FormatTest4(Test& test)
{
    bool value = false;
    bool reference = true;
    std::string output = TestMacrosFormatter::Format("ISHTF_FAIL_IF_EQ", "value", "reference", value, reference);

    ISHTF_FAIL_IF_NEQ(output, "ISHTF_FAIL_IF_EQ(value, reference) failed with actual values (false, true)");
    ISHTF_PASS();
}

void TestMacrosFormatterTests::FormatTest5(Test& test)
{
    int value = 5;
    int reference = 7;
    std::string output = TestMacrosFormatter::Format("ISHTF_FAIL_IF_EQ", "value", "reference", value, reference);

    ISHTF_FAIL_IF_NEQ(output, "ISHTF_FAIL_IF_EQ(value, reference) failed with actual values (5, 7)");
    ISHTF_PASS();
}

enum FormatComparisonTest6Helper
{
    value1 = 1,
    value2 = 5
};

void TestMacrosFormatterTests::FormatTest6(Test& test)
{
    FormatComparisonTest6Helper value = FormatComparisonTest6Helper::value1;
    FormatComparisonTest6Helper reference = FormatComparisonTest6Helper::value2;
    std::string output = TestMacrosFormatter::Format("ISHTF_FAIL_IF_EQ", "value", "reference", value, reference);

    ISHTF_FAIL_IF_NEQ(output, "ISHTF_FAIL_IF_EQ(value, reference) failed with actual values (1, 5)");
    ISHTF_PASS();
}
