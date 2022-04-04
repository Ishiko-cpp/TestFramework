/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTFRAMEWORK_TESTS_CORE_FILECOMPARISONTESTCHECKTESTS_HPP_
#define _ISHIKO_TESTFRAMEWORK_TESTS_CORE_FILECOMPARISONTESTCHECKTESTS_HPP_

#include <Ishiko/Tests/Core.hpp>

class FileComparisonTestCheckTests : public Ishiko::TestSequence
{
public:
    FileComparisonTestCheckTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
};

#endif
