/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "DirectoryComparisonTestCheck.hpp"
#include "FileComparisonTestCheck.hpp"
#include "Test.hpp"
#include <Ishiko/FileSystem.hpp>

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
    m_result = Result::failed;

    Directory outputDirectory(m_outputDirectoryPath);
    Directory referenceDirectory(m_referenceDirectoryPath);

    // TODO: this is a qucik working implementation to be done with it but ideally I'd like the following behaviour.
    // 1. We only iterate through the each directory once.
    // 2. We first check if there are differences in files and then we consider extra or missing files. I think this is
    // more informative for the user in general.

    size_t outputFilesCount = outputDirectory.getRegularFilesCount(false);
    size_t referenceFilesCount = referenceDirectory.getRegularFilesCount(false);

    if (outputFilesCount != referenceFilesCount)
    {
        // TODO: more info, check which files are added or missing
        test.fail(file, line);
        return;
    }

    // TODO: limit the number of files

    bool allCheckPassed = true;
    referenceDirectory.forEachRegularFile(
        [this, &test, file, line, &allCheckPassed](const boost::filesystem::path& referenceFilePath)
        {
            boost::filesystem::path outputFilePath = m_outputDirectoryPath / referenceFilePath.filename();
            std::shared_ptr<FileComparisonTestCheck> check = std::make_shared<FileComparisonTestCheck>(outputFilePath,
                referenceFilePath);
            // TODO: if I add this to the test then I get automatic reporting of each file
            check->run(test, file, line);
            if (check->result() == TestCheck::Result::failed)
            {
                allCheckPassed = false;
            }
        },
        false);

    if (allCheckPassed)
    {
        m_result = Result::passed;
    }
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
