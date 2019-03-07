/*
    Copyright (c) 2007-2019 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "FileComparisonTest.h"
#include "DebugHeap.h"

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
        FILE *file = fopen(m_outputFilePath.string().c_str(), "rb");
        FILE *refFile = fopen(m_referenceFilePath.string().c_str(), "rb");
        
        bool isFileOpen = (file != 0);
        bool isRefFileOpen = (refFile != 0);

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
            }
        }
    }
}

}
}
