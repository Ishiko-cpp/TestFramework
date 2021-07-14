/*
    Copyright (c) 2015-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_CORE_TESTPROGRESSOBSERVER_H_
#define _ISHIKO_TESTS_CORE_TESTPROGRESSOBSERVER_H_

#include "Test.h"
#include "TestNumber.h"
#include "TestResult.h"
#include <string>

namespace Ishiko
{
namespace Tests
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
    std::string m_nesting;
};

}
}

#endif
