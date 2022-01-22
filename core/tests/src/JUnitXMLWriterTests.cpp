/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "JUnitXMLWriterTests.h"
#include <Ishiko/Tests/Core/JUnitXMLWriter.hpp>

using namespace Ishiko::Tests;

JUnitXMLWriterTests::JUnitXMLWriterTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "JUnitXMLWriter tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void JUnitXMLWriterTests::ConstructorTest1(Test& test)
{
    JUnitXMLWriter junitXMLFile;

    ISHIKO_PASS();
}
