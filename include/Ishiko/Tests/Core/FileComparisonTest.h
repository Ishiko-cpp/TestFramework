/*
    Copyright (c) 2007-2019 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_TESTFRAMEWORK_CORE_FILECOMPARISONTEST_H_
#define _ISHIKO_TESTFRAMEWORK_CORE_FILECOMPARISONTEST_H_

#include "Test.h"
#include "TestSequence.h"

namespace Ishiko
{
namespace Tests
{

class FileComparisonTest : public Test
{
public:
    FileComparisonTest(const TestNumber& number, const std::string& name);
    FileComparisonTest(const TestNumber& number, const std::string& name, const TestEnvironment& environment);
    FileComparisonTest(const TestNumber& number, const std::string& name,
        void (*runFct)(FileComparisonTest& test));
    FileComparisonTest(const TestNumber& number, const std::string& name,
        void (*runFct)(FileComparisonTest& test), const TestEnvironment& environment);

    const boost::filesystem::path& getOutputFilePath() const;
    void setOutputFilePath(const boost::filesystem::path& path);

    const boost::filesystem::path& getReferenceFilePath() const;
    void setReferenceFilePath(const boost::filesystem::path& path);

protected:
    void doRun() override;

private:
    void (*m_runFct)(FileComparisonTest& test);
    boost::filesystem::path m_outputFilePath;
    boost::filesystem::path m_referenceFilePath;
};

}
}

#endif
