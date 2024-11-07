// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_TESTFRAMEWORK_CORE_ACTIONS_COPYFILESACTION_HPP
#define GUARD_ISHIKO_CPP_TESTFRAMEWORK_CORE_ACTIONS_COPYFILESACTION_HPP

#include "../TestSetupAction.hpp"
#include <Ishiko/Text.hpp>
#include <utility>

namespace Ishiko
{
    class CopyFilesAction : public TestSetupAction
    {
    public:
        CopyFilesAction(const InterpolatedString& source, const InterpolatedString& destination);

        void setup(const Test& test) override;

    private:
        std::vector<std::pair<InterpolatedString, InterpolatedString>> m_copy_list;
    };
}

#endif
