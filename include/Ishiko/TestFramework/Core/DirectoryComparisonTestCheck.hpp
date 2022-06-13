/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTFRAMEWORK_CORE_DIRECTORYCOMPARISONTESTCHECK_HPP_
#define _ISHIKO_CPP_TESTFRAMEWORK_CORE_DIRECTORYCOMPARISONTESTCHECK_HPP_

#include "TestCheck.hpp"

namespace Ishiko
{

class DirectoryComparisonTestCheck : public TestCheck
{
public:
    DirectoryComparisonTestCheck();
    DirectoryComparisonTestCheck(boost::filesystem::path outputDirectoryPath,
        boost::filesystem::path referenceDirectoryPath);

    void run(Test& test, const char* file, int line) override;

    const boost::filesystem::path& outputDirectoryPath() const;
    void setOutputDirectoryPath(const boost::filesystem::path& path);
    const boost::filesystem::path& referenceDirectoryPath() const;
    void setReferenceDirectoryPath(const boost::filesystem::path& path);

private:
    boost::filesystem::path m_outputDirectoryPath;
    boost::filesystem::path m_referenceDirectoryPath;
};

}

#endif
