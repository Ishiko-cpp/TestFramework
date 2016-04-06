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

#ifndef _ISHIKO_TESTFRAMEWORK_CORE_TESTINFORMATION_H_
#define _ISHIKO_TESTFRAMEWORK_CORE_TESTINFORMATION_H_

#include "TestNumber.h"
#include <string>

namespace Ishiko
{
namespace TestFramework
{

class TestInformation
{
public:
	TestInformation(const TestNumber& number, 
		const std::string& name);
	virtual ~TestInformation() throw();

	const TestNumber& number() const;
	virtual void setNumber(const TestNumber& number);
	const std::string& name() const;

private:
	TestNumber m_number;
	std::string m_name;
};

}
}

#endif
