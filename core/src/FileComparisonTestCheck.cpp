/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "FileComparisonTestCheck.hpp"
#include <Ishiko/BasePlatform.h>
#include <Ishiko/Diff.hpp>
#include <Ishiko/Errors.hpp>

using namespace boost::filesystem;
using namespace std;

namespace Ishiko
{

FileComparisonTestCheck::FileComparisonTestCheck(path outputFilePath, path referenceFilePath)
    : m_outputFilePath(move(outputFilePath)), m_referenceFilePath(move(referenceFilePath))
{
}

FileComparisonTestCheck FileComparisonTestCheck::CreateFromContext(const TestContext& context,
    const path& outputFilePath, const path& referenceFilePath)
{
    return FileComparisonTestCheck(context.getTestOutputPath(outputFilePath),
        context.getReferenceDataPath(referenceFilePath));
}

TestCheck::Result FileComparisonTestCheck::run()
{
    // TODO: fix this file comparison code. It's hacked together at the moment

    // We first try to open the two files
#if ISHIKO_COMPILER == ISHIKO_COMPILER_GCC
    FILE* file = fopen(m_outputFilePath.string().c_str(), "rb");
    FILE* refFile = fopen(m_referenceFilePath.string().c_str(), "rb");
#elif ISHIKO_COMPILER == ISHIKO_COMPILER_MSVC
    FILE* file = nullptr;
    errno_t err = fopen_s(&file, m_outputFilePath.string().c_str(), "rb");
    if (err != 0)
    {
        file = nullptr;
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

    bool isFileOpen = (file != nullptr);
    bool isRefFileOpen = (refFile != nullptr);

    if (!isFileOpen || !isRefFileOpen)
    {
        if (file)
        {
            fclose(file);
        }
        if (refFile)
        {
            fclose(refFile);
        }

        // TODO: more info
        return Result::failed;
    }

    // We managed to open both file, let's compare them

    bool isFileGood;
    bool isRefFileGood;
    char c1;
    char c2;
    int offset = 0;
    while (1)
    {
        size_t n1 = fread(&c1, 1, 1, file);
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
    if (feof(file) != 0)
    {
        isFileEof = true;
    }
    bool isRefFileEof = false;
    if (feof(refFile) != 0)
    {
        isRefFileEof = true;
    }

    // The comparison is finished, close the files
    fclose(file);
    fclose(refFile);

    if (!(isFileEof && isRefFileEof))
    {
        // TODO: where and how to save that diff info
        Error error;
        TextPatch diff = TextDiff::LineDiffFiles(m_referenceFilePath, m_outputFilePath, error);
        if (diff.size() > 0)
        {
            // TODO
        }

        return Result::failed;
    }

    return Result::passed;
}


const path& FileComparisonTestCheck::outputFilePath() const
{
    return m_outputFilePath;
}

const path& FileComparisonTestCheck::referenceFilePath() const
{
    return m_referenceFilePath;
}

}
