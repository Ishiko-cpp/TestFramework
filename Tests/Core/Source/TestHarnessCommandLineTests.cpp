/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#include "TestHarnessCommandLineTests.h"

using namespace Ishiko::Tests;

TestHarnessCommandLineTests::TestHarnessCommandLineTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "TestHarnessCommandLine tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void TestHarnessCommandLineTests::ConstructorTest1(Test& test)
{
}
