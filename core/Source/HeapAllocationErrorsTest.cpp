/*
    Copyright (c) 2000-2019 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "HeapAllocationErrorsTest.h"

namespace Ishiko
{
namespace Tests
{

HeapAllocationErrorsTest::HeapAllocationErrorsTest(const TestNumber& number, const std::string& name,
    void (*runFct)(Test& test))
    : Test(TestNumber(), name), m_innerObserver(std::make_shared<InnerObserver>(*this))
{
    m_test = std::make_shared<Test>(TestNumber(), name, runFct);
    // We pass in a special observer to filter out the lifecycle events as m_test is an implementation detail that
    // shouldn't be visible to the outside.
    m_test->observers().add(m_innerObserver);
}

HeapAllocationErrorsTest::HeapAllocationErrorsTest(const TestNumber& number, const std::string& name,
    void (*runFct)(Test& test), const TestEnvironment& environment)
    : Test(TestNumber(), name, environment), m_innerObserver(std::make_shared<InnerObserver>(*this))
{
    m_test = std::make_shared<Test>(TestNumber(), name, runFct, environment);
    // We pass in a special observer to filter out the lifecycle events as m_test is an implementation detail that
    // shouldn't be visible to the outside.
    m_test->observers().add(m_innerObserver);
}

void HeapAllocationErrorsTest::doRun()
{
    m_test->run();

    setResult(m_test->result());
}

HeapAllocationErrorsTest::InnerObserver::InnerObserver(Test& test)
    : m_test(test)
{
}

void HeapAllocationErrorsTest::InnerObserver::onCheckFailed(const Test& source, const std::string& message,
    const char* file, int line)
{
    m_test.observers().notifyCheckFailed(source, message, file, line);
}

}
}
