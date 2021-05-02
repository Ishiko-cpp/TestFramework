/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#include "TestMacrosFormatter.h"

namespace Ishiko
{
namespace Tests
{

bool TestMacrosFormatter::UniversalFormatter<char*>::Format(const char* value, std::string& output)
{
    output = value;
    return true;
}

bool TestMacrosFormatter::UniversalFormatter<std::string>::Format(const std::string& value, std::string& output)
{
    output = value;
    return true;
}

bool TestMacrosFormatter::UniversalFormatter<bool>::Format(bool value, std::string& output)
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
}
