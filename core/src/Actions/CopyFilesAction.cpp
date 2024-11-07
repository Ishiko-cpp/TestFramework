// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "Actions/CopyFilesAction.hpp"
#include "Test.hpp"
#include <Ishiko/FileSystem.hpp>

using namespace Ishiko;

CopyFilesAction::CopyFilesAction(const InterpolatedString& source, const InterpolatedString& destination)
{
    m_copy_list.emplace_back(source, destination);
}

void CopyFilesAction::setup(const Test& test)
{
    for (const std::pair<InterpolatedString, InterpolatedString>& source_destination_pair : m_copy_list)
    {
        boost::filesystem::path source = source_destination_pair.first.expand(test.context());
        boost::filesystem::path destination = source_destination_pair.second.expand(test.context());
        FileSystem::CopySingleFile(source, destination);
    }
}
