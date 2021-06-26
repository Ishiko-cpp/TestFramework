/*
    Copyright (c) 2015-2019 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_TESTFRAMEWORK_CORE_FILESTEARDOWNACTION_H_
#define _ISHIKO_TESTFRAMEWORK_CORE_FILESTEARDOWNACTION_H_

#include "TestTeardownAction.h"
#include <boost/filesystem/path.hpp>
#include <vector>

namespace Ishiko
{
namespace Tests
{

class FilesTeardownAction : public TestTeardownAction
{
public:
    void teardown() override;

    void add(const boost::filesystem::path& path);

private:
    std::vector<boost::filesystem::path> d_files;
};

}
}

#endif
