/*
	Copyright (c) 2005-2015 Xavier Leclercq

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

#ifndef _ISHIKO_TESTFRAMEWORK_CORE_TEST_H_
#define _ISHIKO_TESTFRAMEWORK_CORE_TEST_H_

#include "TestInformation.h"
#include "TestResult.h"
#include "TestEnvironment.h"
#include "TestObserver.h"
#include "TestTeardownAction.h"
#include <string>

namespace Ishiko
{
namespace TestFramework
{

class Test
{
public:
	Test(const TestNumber& number, const std::string& name);
	Test(const TestNumber& number, const std::string& name, 
		const TestEnvironment& environment);
	virtual ~Test() throw();
	
	const TestNumber& number() const;
	const std::string& name() const;
	TestInformation& information();
	const TestResult& result() const;
	bool passed() const;
	const TestEnvironment& environment() const;
	
	virtual void run();
	virtual void run(TestObserver::ptr& observer);

	virtual void addTeardownAction(std::shared_ptr<TestTeardownAction>& action);
	template<class ActionClass> void addTeardownAction(std::shared_ptr<ActionClass>& action);

protected:
	virtual void teardown();
	virtual TestResult::EOutcome doRun(TestObserver::ptr& observer) = 0;
	virtual void notify(TestObserver::EEventType type,
		TestObserver::ptr& observer);
	
private:
	TestInformation m_information;
	TestResult m_result;
	const TestEnvironment& m_environment;
	std::vector<std::shared_ptr<TestTeardownAction> > m_teardownActions;
};

template<class ActionClass>
void Test::addTeardownAction(std::shared_ptr<ActionClass>& action)
{
	addTeardownAction((std::shared_ptr<TestTeardownAction>&)action);
}

}
}

#endif
