/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "FileComparisonTestCheckTests.hpp"

using namespace Ishiko;

FileComparisonTestCheckTests::FileComparisonTestCheckTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "FileComparisonTestCheck tests", context)
{
}
