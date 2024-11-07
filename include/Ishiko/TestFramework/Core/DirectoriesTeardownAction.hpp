// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_TESTFRAMEWORK_CORE_DIRECTORIESTEARDOWNACTION_HPP
#define GUARD_ISHIKO_CPP_TESTFRAMEWORK_CORE_DIRECTORIESTEARDOWNACTION_HPP

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
