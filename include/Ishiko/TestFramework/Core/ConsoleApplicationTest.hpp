/*
    Copyright (c) 2016-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTFRAMEWORK_CORE_CONSOLEAPPLICATIONTEST_HPP_
#define _ISHIKO_CPP_TESTFRAMEWORK_CORE_CONSOLEAPPLICATIONTEST_HPP_

#include "FileComparisonTestCheck.hpp"
#include "Test.hpp"
#include <boost/filesystem.hpp>
#include <string>

namespace Ishiko
{

class ConsoleApplicationTest : public Test
{
public:
    ConsoleApplicationTest(const TestNumber& number, const std::string& name, const std::string& commandLine,
        int expectedExitCode);
    ConsoleApplicationTest(const TestNumber& number, const std::string& name, const std::string& commandLine,
        int expectedExitCode, const TestContext& context);
    
    void setStandardOutputFilePath(const boost::filesystem::path& path);
    void setStandardOutputReferenceFilePath(const boost::filesystem::path& path);

protected:
    void doRun() override;

private:
    std::string m_commandLine;
    bool m_checkExitCode;
    int m_expectedExitCode;
    FileComparisonTestCheck m_standardOutputTest;
};

}

#endif
