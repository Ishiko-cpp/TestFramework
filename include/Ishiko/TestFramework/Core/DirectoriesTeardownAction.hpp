/*
    Copyright (c) 2015-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTFRAMEWORK_CORE_DIRECTORIESTEARDOWNACTION_HPP_
#define _ISHIKO_CPP_TESTFRAMEWORK_CORE_DIRECTORIESTEARDOWNACTION_HPP_

#include "TestTeardownAction.hpp"
#include <boost/filesystem/path.hpp>
#include <vector>

namespace Ishiko
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

#endif
