/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTFRAMEWORK_CORE_DIRECTORYCOMPARISONTESTCHECK_HPP_
#define _ISHIKO_CPP_TESTFRAMEWORK_CORE_DIRECTORYCOMPARISONTESTCHECK_HPP_

#include "TestCheck.hpp"

namespace Ishiko
{

class DirectoryComparisonTestCheck : public TestCheck
{
public:
    void run(Test& test, const char* file, int line) override;
};

}

#endif
