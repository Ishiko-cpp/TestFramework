/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_TESTFRAMEWORK_CORE_TESTMACROSFORMATTER_H_
#define _ISHIKO_TESTFRAMEWORK_CORE_TESTMACROSFORMATTER_H_

#include <string>
#include <type_traits>

namespace Ishiko
{
namespace Tests
{

namespace Internal
{

template <typename T, typename Enable = void>
class UniversalFormatter
{
public:
    static bool Format(const T& value, std::string& output);
};

template <>
class UniversalFormatter<char*>
{
public:
    static bool Format(const char* value, std::string& output);
};

template <>
class UniversalFormatter<std::string>
{
public:
    static bool Format(const std::string& value, std::string& output);
};

template <>
class UniversalFormatter<bool>
{
public:
    static bool Format(bool value, std::string& output);
};

template <typename T>
class UniversalFormatter<T, typename std::enable_if<std::is_integral<T>::value>::type>
{
public:
    static bool Format(T value, std::string& output);
};

template <typename T>
class UniversalFormatter<T, typename std::enable_if<!std::is_integral<T>::value && std::is_convertible<T, int>::value>::type>
{
public:
    static bool Format(T value, std::string& output);
};

}

class TestMacrosFormatter
{
public:
    template <typename V>
    static std::string Format(const std::string& macro, const std::string& valueString, const V& value);

    template <typename V1, typename V2>
    static std::string Format(const std::string& macro, const std::string& value1String,
        const std::string& value2String, const V1& value1, const V2& value2);
};

template <typename V>
std::string TestMacrosFormatter::Format(const std::string& macro, const std::string& valueString, const V& value)
{
    std::string result;

    result += macro + "(" + valueString + ") failed with actual value (";

    std::string formattedValue;
    Internal::UniversalFormatter<typename std::decay<V>::type>::Format(value, formattedValue);
    result += formattedValue;

    result += ")";

    return result;
}

template <typename V1, typename V2>
std::string TestMacrosFormatter::Format(const std::string& macro, const std::string& value1String,
    const std::string& value2String, const V1& value1, const V2& value2)
{
    std::string result;

    result += macro + "(" + value1String + ", " + value2String + ") failed with actual values (";

    std::string formattedValue1;
    Internal::UniversalFormatter<typename std::decay<V1>::type>::Format(value1, formattedValue1);
    result += formattedValue1;

    result += ", ";

    std::string formattedValue2;
    Internal::UniversalFormatter<typename std::decay<V2>::type>::Format(value2, formattedValue2);
    result += formattedValue2;

    result += ")";

    return result;
}

template <typename T, typename Enable>
bool Internal::UniversalFormatter<T, Enable>::Format(const T& value, std::string& output)
{
    return false;
}

template <typename T>
bool Internal::UniversalFormatter<T, typename std::enable_if<std::is_integral<T>::value>::type>::Format(T value, std::string& output)
{
    output = std::to_string(value);
    return true;
}

template <typename T>
bool Internal::UniversalFormatter<T, typename std::enable_if<!std::is_integral<T>::value && std::is_convertible<T, int>::value>::type>::Format(T value, std::string& output)
{
    output = std::to_string(value);
    return true;
}

}
}

#endif
