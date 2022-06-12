/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTCHECK_HPP_
#define _ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTCHECK_HPP_

#include "JUnitXMLWriter.hpp"

namespace Ishiko
{

class Test;

// TODO: make this an inner class?
class TestCheck
{
public:
    enum class Result
    {
        passed,
        failed
    };

    TestCheck();

    virtual void run(Test& test, const char* file, int line) = 0;

    Result result() const noexcept;

    virtual void addToJUnitXMLTestReport(JUnitXMLWriter& writer) const;

protected:
    Result m_result;
};

}

#endif
