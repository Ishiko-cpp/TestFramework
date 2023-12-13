/*
    Copyright (c) 2021-2023 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "TestMacrosFormatter.hpp"

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
    output = value;
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
