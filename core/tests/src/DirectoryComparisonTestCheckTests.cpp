/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "DirectoryComparisonTestCheckTests.hpp"

using namespace Ishiko;

DirectoryComparisonTestCheckTests::DirectoryComparisonTestCheckTests(const TestNumber& number,
    const TestContext& context)
    : TestSequence(number, "DirectoryComparisonTestCheck tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void DirectoryComparisonTestCheckTests::ConstructorTest1(Test& test)
{
    DirectoryComparisonTestCheck directoryComparisonCheck;

    ISHIKO_TEST_PASS();
}
