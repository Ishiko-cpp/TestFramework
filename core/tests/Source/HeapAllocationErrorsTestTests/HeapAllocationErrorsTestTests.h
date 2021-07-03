/*
    Copyright (c) 2007-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_TESTS_CORE_HEAPALLOCATIONERRORSTESTTESTS_HEAPALLOCATIONERRORSTESTTESTS_H_
#define _ISHIKO_TESTS_TESTS_CORE_HEAPALLOCATIONERRORSTESTTESTS_HEAPALLOCATIONERRORSTESTTESTS_H_

#include <Ishiko/Tests/Core.h>

class HeapAllocationErrorsTestTests : public Ishiko::Tests::TestSequence
{
public:
    HeapAllocationErrorsTestTests(const Ishiko::Tests::TestNumber& number,
        const Ishiko::Tests::TestEnvironment& environment);

private:
    static void CreationTest1(Ishiko::Tests::Test& test);
};

#endif
