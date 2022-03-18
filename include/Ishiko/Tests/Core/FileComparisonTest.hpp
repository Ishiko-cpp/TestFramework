/*
    Copyright (c) 2007-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTS_CORE_FILECOMPARISONTEST_HPP_
#define _ISHIKO_CPP_TESTS_CORE_FILECOMPARISONTEST_HPP_

#include "Test.hpp"
#include "TestSequence.hpp"

namespace Ishiko
{

class FileComparisonTest : public Test
{
public:
    FileComparisonTest(const TestNumber& number, const std::string& name);
    FileComparisonTest(const TestNumber& number, const std::string& name, const TestContext& context);
    FileComparisonTest(const TestNumber& number, const std::string& name,
        void (*runFct)(FileComparisonTest& test));
    FileComparisonTest(const TestNumber& number, const std::string& name,
        void (*runFct)(FileComparisonTest& test), const TestContext& context);

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

#endif
