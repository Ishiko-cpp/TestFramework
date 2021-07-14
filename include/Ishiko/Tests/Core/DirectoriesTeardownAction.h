/*
    Copyright (c) 2015-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_CORE_DIRECTORIESTEARDOWNACTION_H_
#define _ISHIKO_TESTS_CORE_DIRECTORIESTEARDOWNACTION_H_

#include "TestTeardownAction.h"
#include <boost/filesystem/path.hpp>
#include <vector>

namespace Ishiko
{
namespace Tests
{

class DirectoriesTeardownAction : public TestTeardownAction
{
public:
    void teardown() override;

    void add(const boost::filesystem::path& path);

private:
    std::vector<boost::filesystem::path> d_directories;
};

}
}

#endif
