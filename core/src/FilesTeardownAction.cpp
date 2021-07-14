/*
    Copyright (c) 2015-2019 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#include "FilesTeardownAction.h"
#include <boost/filesystem/operations.hpp>

namespace Ishiko
{
namespace Tests
{

void FilesTeardownAction::teardown()
{
    for (size_t i = 0; i < d_files.size(); ++i)
    {
        boost::filesystem::remove(d_files[i]);
    }
}

void FilesTeardownAction::add(const boost::filesystem::path& path)
{
    d_files.push_back(path);
}

}
}
