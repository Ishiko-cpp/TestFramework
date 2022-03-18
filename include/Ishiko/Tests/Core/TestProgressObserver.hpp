/*
    Copyright (c) 2015-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTS_CORE_TESTPROGRESSOBSERVER_HPP_
#define _ISHIKO_CPP_TESTS_CORE_TESTPROGRESSOBSERVER_HPP_

#include "Test.hpp"
#include "TestNumber.hpp"
#include "TestResult.hpp"
#include <string>

namespace Ishiko
{

class TestProgressObserver : public Test::Observer
{
public:
    TestProgressObserver(std::ostream& output);

    void onLifecycleEvent(const Test& source, EEventType type) override;
    void onCheckFailed(const Test& source, const std::string& message, const char* file, int line) override;
    void onExceptionThrown(const Test& source, std::exception_ptr exception) override;

protected:
    static std::string formatNumber(const TestNumber& number);
    static std::string formatResult(const TestResult& result);

private:
    std::ostream& m_output;
    size_t m_nestingLevel;
};

}

#endif
