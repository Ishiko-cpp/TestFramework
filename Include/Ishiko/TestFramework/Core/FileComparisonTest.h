/*
	Copyright (c) 2007-2015 Xavier Leclercq

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

#ifndef _ISHIKO_TESTFRAMEWORK_CORE_FILECOMPARISONTEST_H_
#define _ISHIKO_TESTFRAMEWORK_CORE_FILECOMPARISONTEST_H_

#include "Test.h"
#include "TestSequence.h"

namespace Ishiko
{
namespace TestFramework
{

class FileComparisonTest : public Test
{
public:
    FileComparisonTest(const TestNumber& number,
        const std::string& name);
	FileComparisonTest(const TestNumber& number,
		const std::string& name,
		TestResult::EOutcome (*runFct)(FileComparisonTest& test));
	FileComparisonTest(const std::string& name,
		TestResult::EOutcome (*runFct)(FileComparisonTest& test),
		TestSequence& parentSequence);
	virtual ~FileComparisonTest();

    const boost::filesystem::path& getOutputFilePath() const;
	void setOutputFilePath(const boost::filesystem::path& path);

    const boost::filesystem::path& getReferenceFilePath() const;
	void setReferenceFilePath(const boost::filesystem::path& path);

protected:
	virtual TestResult::EOutcome doRun(TestObserver::ptr& observer);

private:
	TestResult::EOutcome (*m_runFct)(FileComparisonTest& test);
	boost::filesystem::path m_outputFilePath;
	boost::filesystem::path m_referenceFilePath;
};

}
}

#endif
