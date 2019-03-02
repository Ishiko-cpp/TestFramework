/*
    Copyright (c) 2015-2019 Xavier Leclercq

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

#ifndef _ISHIKO_TESTFRAMEWORK_CORE_TESTPROGRESSOBSERVER_H_
#define _ISHIKO_TESTFRAMEWORK_CORE_TESTPROGRESSOBSERVER_H_

#include "TestObserver.h"
#include "TestNumber.h"
#include "TestResult.h"
#include <string>

namespace Ishiko
{
namespace TestFramework
{

class TestProgressObserver : public TestObserver
{
public:
    TestProgressObserver();
    virtual ~TestProgressObserver() throw();

protected:
    virtual void notify(EEventType type, const Test& test);

    static std::string formatNumber(const TestNumber& number);
    static std::string formatResult(const TestResult& result);

private:
    std::string m_nesting;
};

}
}

#endif
