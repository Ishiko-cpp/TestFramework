/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTFRAMEWORK_CORE_FILECOMPARISONTESTCHECK_HPP_
#define _ISHIKO_CPP_TESTFRAMEWORK_CORE_FILECOMPARISONTESTCHECK_HPP_

#include "TestCheck.hpp"
#include "TestContext.hpp"
#include <boost/filesystem.hpp>

namespace Ishiko
{

class FileComparisonTestCheck : public TestCheck
{
public:
    FileComparisonTestCheck();
    FileComparisonTestCheck(boost::filesystem::path outputFilePath, boost::filesystem::path referenceFilePath);
    static FileComparisonTestCheck CreateFromContext(const TestContext& context,
        const boost::filesystem::path& outputAndReferenceFilePath);
    static FileComparisonTestCheck CreateFromContext(const TestContext& context,
        const boost::filesystem::path& outputFilePath, const boost::filesystem::path& referenceFilePath);

    void run(Test& test, const char* file, int line) override;

    const boost::filesystem::path& outputFilePath() const;
    void setOutputFilePath(const boost::filesystem::path& path);
    const boost::filesystem::path& referenceFilePath() const;
    void setReferenceFilePath(const boost::filesystem::path& path);

private:
    boost::filesystem::path m_outputFilePath;
    boost::filesystem::path m_referenceFilePath;
};

}

#endif
