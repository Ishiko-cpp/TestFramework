/*
    Copyright (c) 2007-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_TESTS_CORE_HEAPALLOCATIONERRORSTESTTESTS_HEAPALLOCATIONERRORSTESTTESTS_H_
#define _ISHIKO_TESTS_TESTS_CORE_HEAPALLOCATIONERRORSTESTTESTS_HEAPALLOCATIONERRORSTESTTESTS_H_

#include <Ishiko/TestFramework/Core.hpp>

class HeapAllocationErrorsTestTests : public Ishiko::TestSequence
{
public:
    HeapAllocationErrorsTestTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void CreationTest1(Ishiko::Test& test);
};

#endif
