/*
    Copyright (c) 2016-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_CORE_CONSOLEAPPLICATIONTEST_H_
#define _ISHIKO_TESTS_CORE_CONSOLEAPPLICATIONTEST_H_

#include "Test.h"
#include "FileComparisonTest.h"
#include <string>

namespace Ishiko
{
namespace Tests
{

class ConsoleApplicationTest : public Test
{
public:
    ConsoleApplicationTest(const TestNumber& number, const std::string& name, const std::string& commandLine,
        int expectedExitCode);
    ConsoleApplicationTest(const TestNumber& number, const std::string& name, const std::string& commandLine,
        int expectedExitCode, const TestEnvironment& environment);
    
    void setStandardOutputFilePath(const boost::filesystem::path& path);
    void setStandardOutputReferenceFilePath(const boost::filesystem::path& path);

protected:
    void doRun() override;

private:
    std::string m_commandLine;
    bool m_checkExitCode;
    int m_expectedExitCode;
    FileComparisonTest m_standardOutputTest;
};

}
}

#endif
