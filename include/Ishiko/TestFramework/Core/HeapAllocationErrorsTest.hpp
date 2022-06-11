/*
    Copyright (c) 2000-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTFRAMEWORK_CORE_HEAPALLOCATIONERRORSTEST_HPP_
#define _ISHIKO_CPP_TESTFRAMEWORK_CORE_HEAPALLOCATIONERRORSTEST_HPP_

#include "Test.hpp"
#include "TestSequence.hpp"

namespace Ishiko
{

class HeapAllocationErrorsTest : public Test
{
public:
    HeapAllocationErrorsTest(const TestNumber& number, const std::string& name,
        void (*runFct)(Test& test));
    HeapAllocationErrorsTest(const TestNumber& number, const std::string& name,
        void (*runFct)(Test& test), const TestContext& context);

    void addToJUnitXMLTestReport(JUnitXMLWriter& writer) const;

protected:
    void doRun() override;

private:
    class InnerObserver : public Observer
    {
    public:
        InnerObserver(Test& test);

        void onCheckFailed(const Test& source, const std::string& message, const char* file, int line) override;
        void onExceptionThrown(const Test& source, std::exception_ptr exception) override;

    private:
        Test& m_test;
    };

    std::shared_ptr<Test> m_test;
    std::shared_ptr<InnerObserver> m_innerObserver;
};

}

#endif
