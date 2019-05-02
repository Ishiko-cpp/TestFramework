/*
    Copyright (c) 2019 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "TestNumberTests.h"

using namespace Ishiko::Tests;

TestNumberTests::TestNumberTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "TestNumber tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
    append<HeapAllocationErrorsTest>("getDeeperNumber test 1", GetDeeperNumberTest1);
}

void TestNumberTests::ConstructorTest1(Test& test)
{
    TestNumber number;

    ISHTF_FAIL_UNLESS(number.depth() == 0);
    ISHTF_PASS();
}

void TestNumberTests::ConstructorTest2(Test& test)
{
    TestNumber number(2);

    ISHTF_FAIL_UNLESS(number.depth() == 1);
    ISHTF_FAIL_UNLESS(number.part(0) == 2);
    ISHTF_PASS();
}

void TestNumberTests::GetDeeperNumberTest1(Ishiko::Tests::Test& test)
{
    TestNumber number;
    TestNumber deeperNumber = number.getDeeperNumber();

    ISHTF_FAIL_UNLESS(deeperNumber.depth() == 1);
    ISHTF_FAIL_UNLESS(deeperNumber.part(0) == 1);
    ISHTF_PASS();
}
