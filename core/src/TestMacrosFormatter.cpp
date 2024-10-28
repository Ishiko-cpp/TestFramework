// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "TestMacrosFormatter.hpp"
#include <cstring>

namespace Ishiko
{

bool Internal::UniversalFormatter<char*>::Format(const char* value, std::string& output)
{
    size_t value_length = strlen(value);
    output.reserve(value_length + 2);
    output.push_back('"');
    output.append(value, value_length);
    output.push_back('"');
    return true;
}

bool Internal::UniversalFormatter<std::string>::Format(const std::string& value, std::string& output)
{
    output.reserve(value.size() + 3);
    output.push_back('"');
    output.append(value);
    output.append("\"s");
    return true;
}

bool Internal::UniversalFormatter<bool>::Format(bool value, std::string& output)
{
    if (value)
    {
        output = "true";
    }
    else
    {
        output = "false";
    }
    return true;
}

}
