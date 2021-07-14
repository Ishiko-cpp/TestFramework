/*
    Copyright (c) 2000-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_CORE_HEAPALLOCATIONERRORSTEST_H_
#define _ISHIKO_TESTS_CORE_HEAPALLOCATIONERRORSTEST_H_

#include "Test.h"
#include "TestSequence.h"

namespace Ishiko
{
namespace Tests
{

class HeapAllocationErrorsTest : public Test
{
public:
    HeapAllocationErrorsTest(const TestNumber& number, const std::string& name,
        void (*runFct)(Test& test));
    HeapAllocationErrorsTest(const TestNumber& number, const std::string& name,
        void (*runFct)(Test& test), const TestEnvironment& environment);

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
}

#endif
