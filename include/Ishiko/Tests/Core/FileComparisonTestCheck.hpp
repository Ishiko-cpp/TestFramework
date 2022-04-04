/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTFRAMEWORK_CORE_FILECOMPARISONTESTCHECK_HPP_
#define _ISHIKO_CPP_TESTFRAMEWORK_CORE_FILECOMPARISONTESTCHECK_HPP_

#include "TestCheck.hpp"
#include <boost/filesystem.hpp>

namespace Ishiko
{

class FileComparisonTestCheck : public TestCheck
{
public:
    FileComparisonTestCheck(boost::filesystem::path outputFilePath, boost::filesystem::path referenceFilePath);

    Result run() override;

private:
    boost::filesystem::path m_outputFilePath;
    boost::filesystem::path m_referenceFilePath;
};

}

#endif
