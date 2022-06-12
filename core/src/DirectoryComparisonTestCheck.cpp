/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "DirectoryComparisonTestCheck.hpp"

using namespace Ishiko;

DirectoryComparisonTestCheck::DirectoryComparisonTestCheck()
{
}

DirectoryComparisonTestCheck::DirectoryComparisonTestCheck(boost::filesystem::path outputDirectoryPath,
    boost::filesystem::path referenceDirectoryPath)
    : m_outputDirectoryPath(std::move(outputDirectoryPath)),
    m_referenceDirectoryPath(std::move(referenceDirectoryPath))
{
}

void DirectoryComparisonTestCheck::run(Test& test, const char* file, int line)
{
    // TODO
}

const boost::filesystem::path& DirectoryComparisonTestCheck::outputDirectoryPath() const
{
    return m_outputDirectoryPath;
}

void DirectoryComparisonTestCheck::setOutputDirectoryPath(const boost::filesystem::path& path)
{
    m_outputDirectoryPath = path;
}

const boost::filesystem::path& DirectoryComparisonTestCheck::referenceDirectoryPath() const
{
    return m_referenceDirectoryPath;
}

void DirectoryComparisonTestCheck::setReferenceDirectoryPath(const boost::filesystem::path& path)
{
    m_referenceDirectoryPath = path;
}
