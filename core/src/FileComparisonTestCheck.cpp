/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "FileComparisonTestCheck.hpp"
#include "Test.hpp"
#include <Ishiko/BasePlatform.h>
#include <Ishiko/Diff.hpp>
#include <Ishiko/Errors.hpp>
#include <Ishiko/FileSystem.hpp>

using namespace Ishiko;

FileComparisonTestCheck::FileComparisonTestCheck()
{
}

FileComparisonTestCheck::FileComparisonTestCheck(boost::filesystem::path outputFilePath,
    boost::filesystem::path referenceFilePath)
    : m_outputFilePath(std::move(outputFilePath)), m_referenceFilePath(std::move(referenceFilePath))
{
}

FileComparisonTestCheck FileComparisonTestCheck::CreateFromContext(const TestContext& context,
    const boost::filesystem::path& outputAndReferenceFilePath)
{
    return FileComparisonTestCheck(context.getOutputPath(outputAndReferenceFilePath),
        context.getReferencePath(outputAndReferenceFilePath));
}

FileComparisonTestCheck FileComparisonTestCheck::CreateFromContext(const TestContext& context,
    const boost::filesystem::path& outputFilePath, const boost::filesystem::path& referenceFilePath)
{
    return FileComparisonTestCheck(context.getOutputPath(outputFilePath), context.getReferencePath(referenceFilePath));
}

void FileComparisonTestCheck::run(Test& test, const char* file, int line)
{
    // TODO: fix this file comparison code. It's hacked together at the moment

    m_result = Result::failed;

    // We first try to open the two files
#if ISHIKO_COMPILER == ISHIKO_COMPILER_GCC
    FILE* outputFile = fopen(m_outputFilePath.string().c_str(), "rb");
    FILE* refFile = fopen(m_referenceFilePath.string().c_str(), "rb");
#elif ISHIKO_COMPILER == ISHIKO_COMPILER_MSVC
    FILE* outputFile = nullptr;
    errno_t err = fopen_s(&outputFile, m_outputFilePath.string().c_str(), "rb");
    if (err != 0)
    {
        outputFile = nullptr;
    }
    FILE* refFile = nullptr;
    err = fopen_s(&refFile, m_referenceFilePath.string().c_str(), "rb");
    if (err != 0)
    {
        refFile = nullptr;
    }
#else
    #error Unsupported or unrecognized compiler
#endif

    bool isFileOpen = (outputFile != nullptr);
    bool isRefFileOpen = (refFile != nullptr);

    if (!isFileOpen || !isRefFileOpen)
    {
        if (outputFile)
        {
            fclose(outputFile);
        }
        if (refFile)
        {
            fclose(refFile);
        }

        // TODO: more info
        test.fail(file, line);
        return;
    }

    // We managed to open both file, let's compare them

    bool isFileGood;
    bool isRefFileGood;
    char c1;
    char c2;
    int offset = 0;
    while (1)
    {
        size_t n1 = fread(&c1, 1, 1, outputFile);
        size_t n2 = fread(&c2, 1, 1, refFile);
        isFileGood = (n1 == 1);
        isRefFileGood = (n2 == 1);
        if (!isFileGood || !isRefFileGood || (c1 != c2))
        {
            break;
        }
        offset++;
    }

    bool isFileEof = false;
    if (feof(outputFile) != 0)
    {
        isFileEof = true;
    }
    bool isRefFileEof = false;
    if (feof(refFile) != 0)
    {
        isRefFileEof = true;
    }

    // The comparison is finished, close the files
    fclose(outputFile);
    fclose(refFile);

    if (!(isFileEof && isRefFileEof))
    {
        test.fail(file, line);

        Error error;
        TextPatch diff = TextDiff::LineDiffFiles(m_outputFilePath, m_referenceFilePath, error);
        if (diff.size() > 0)
        {
            m_firstDifferentLine = diff[0].text();
            test.fail(m_firstDifferentLine, file, line);   
        }

        // TODO: have a toggle on command line to explicitly enable this?

        Error persistenceError;
        boost::filesystem::path persistentStoragePath = test.context().getOutputDirectory("persistent-storage", persistenceError);
        // TODO: ignore error only if the error is not found
        if (!persistenceError)
        {
            boost::filesystem::path targetDirectory = persistentStoragePath / test.name();
            // TODO: CopyFile option to do that
            boost::filesystem::create_directories(targetDirectory);
            FileSystem::CopyFile(m_outputFilePath, (targetDirectory / m_outputFilePath.filename()), persistenceError);
            FileSystem::CopyFile(m_referenceFilePath, (targetDirectory / m_referenceFilePath.filename()), persistenceError);

            // TODO: what do if we cannot copy the files?
        }
    }
    else
    {
        m_result = Result::passed;
    }
}

const boost::filesystem::path& FileComparisonTestCheck::outputFilePath() const
{
    return m_outputFilePath;
}

void FileComparisonTestCheck::setOutputFilePath(const boost::filesystem::path& path)
{
    m_outputFilePath = path;
}

const boost::filesystem::path& FileComparisonTestCheck::referenceFilePath() const
{
    return m_referenceFilePath;
}

void FileComparisonTestCheck::setReferenceFilePath(const boost::filesystem::path& path)
{
    m_referenceFilePath = path;
}

void FileComparisonTestCheck::addToJUnitXMLTestReport(JUnitXMLWriter& writer) const
{
    writer.writeText("File comparison between output ");
    writer.writeText(m_outputFilePath.string());
    writer.writeText(" and reference ");
    writer.writeText(m_referenceFilePath.string());
    writer.writeText(" failed.");
    writer.writeText(m_firstDifferentLine);
}
