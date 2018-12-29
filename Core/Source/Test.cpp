/*
	Copyright (c) 2006-2015 Xavier Leclercq

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

#include "Test.h"

namespace Ishiko
{
namespace TestFramework
{

Test::Test(const TestNumber& number, 
	       const std::string& name)
	: m_information(number, name), m_result(*this),
	m_environment(TestEnvironment::defaultTestEnvironment())
{
}

Test::Test(const TestNumber& number,
	const std::string& name,
	const TestEnvironment& environment)
	: m_information(number, name), m_result(*this),
	m_environment(environment)
{
}

Test::~Test() throw()
{
}

const TestNumber& Test::number() const
{
	return m_information.number();
}

const std::string& Test::name() const
{
	return m_information.name();
}

TestInformation& Test::information()
{
	return m_information;
}

const TestResult& Test::result() const
{
	return m_result;
}

bool Test::passed() const
{
	return m_result.passed();
}

void Test::run()
{
	TestObserver::ptr observer = std::make_shared<TestObserver>();
	run(observer);
}

void Test::run(TestObserver::ptr& observer)
{
	notify(TestObserver::eTestStart, observer);

    setup();

	TestResult::EOutcome outcome = TestResult::eFailed;
	try
	{
		outcome = doRun(observer);
	}
	catch (...)
	{
		outcome = TestResult::eException;
	}

	m_result.setOutcome(outcome);

	teardown();

	notify(TestObserver::eTestEnd, observer);
}

void Test::addSetupAction(std::shared_ptr<TestSetupAction> action)
{
    m_setupActions.push_back(action);
}

void Test::addTeardownAction(std::shared_ptr<TestTeardownAction> action)
{
	m_teardownActions.push_back(action);
}

void Test::setup()
{
    for (size_t i = 0; i < m_setupActions.size(); ++i)
    {
        m_setupActions[i]->setup();
    }
}

void Test::teardown()
{
	for (size_t i = 0; i < m_teardownActions.size(); ++i)
	{
		m_teardownActions[i]->teardown();
	}
}

void Test::notify(TestObserver::EEventType type,
				  TestObserver::ptr& observer)
{
	if (observer)
	{
		observer->notify(type, *this);
	}
}

const TestEnvironment& Test::environment() const
{
	return m_environment;
}

}
}
