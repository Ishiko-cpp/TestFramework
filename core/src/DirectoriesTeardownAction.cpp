/*
    Copyright (c) 2015-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "DirectoriesTeardownAction.hpp"
#include <boost/filesystem/operations.hpp>

namespace Ishiko
{
namespace Tests
{

void DirectoriesTeardownAction::teardown()
{
    for (size_t i = 0; i < d_directories.size(); ++i)
    {
        boost::filesystem::remove(d_directories[i]);
    }
}

void DirectoriesTeardownAction::add(const boost::filesystem::path& path)
{
    d_directories.push_back(path);
}

}
}
