/*
    Copyright (c) 2007-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "FileComparisonTest.hpp"
#include "DebugHeap.hpp"
#include <Ishiko/Diff.h>
#include <Ishiko/BasePlatform.h>

using namespace Ishiko::Diff;

namespace Ishiko
{
namespace Tests
{

FileComparisonTest::FileComparisonTest(const TestNumber& number, const std::string& name)
    : Test(number, name), m_runFct(0)
{
}

FileComparisonTest::FileComparisonTest(const TestNumber& number, const std::string& name,
    const TestEnvironment& environment)
    : Test(number, name, environment), m_runFct(0)
{
}

FileComparisonTest::FileComparisonTest(const TestNumber& number, const std::string& name,
    void (*runFct)(FileComparisonTest& test))
    : Test(number, name), m_runFct(runFct)
{
}

FileComparisonTest::FileComparisonTest(const TestNumber& number, const std::string& name,
    void (*runFct)(FileComparisonTest& test), const TestEnvironment& environment)
    : Test(number, name, environment), m_runFct(runFct)
{
}

void FileComparisonTest::setOutputFilePath(const boost::filesystem::path& path)
{
    DebugHeap::TrackingState trackingState;
    trackingState.disableTracking();

    m_outputFilePath = path;

    trackingState.restore();
}

void FileComparisonTest::setReferenceFilePath(const boost::filesystem::path& path)
{
    DebugHeap::TrackingState trackingState;
    trackingState.disableTracking();

    m_referenceFilePath = path;

    trackingState.restore();
}

const boost::filesystem::path& FileComparisonTest::getOutputFilePath() const
{
    return m_outputFilePath;
}

const boost::filesystem::path& FileComparisonTest::getReferenceFilePath() const
{
    return m_referenceFilePath;
}

void FileComparisonTest::doRun()
{
    if (m_runFct)
    {
        m_runFct(*this);
    }
    else
    {
        pass();
    }

    if (passed())
    {
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

            fail(__FILE__, __LINE__);
        }

        if (passed())
        {
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
                fail(__FILE__, __LINE__);

                Error error;
                TextPatch diff  = TextDiff::LineDiffFiles(m_referenceFilePath, m_outputFilePath, error);
                if (diff.size() > 0)
                {
                    fail(diff[0].text(), __FILE__, __LINE__);
                }
            }
        }
    }
}

}
}
