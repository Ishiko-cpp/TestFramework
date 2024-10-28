// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_TESTFRAMEWORK_CORE_HEAPALLOCATIONERRORSTEST_HPP
#define GUARD_ISHIKO_CPP_TESTFRAMEWORK_CORE_HEAPALLOCATIONERRORSTEST_HPP

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
