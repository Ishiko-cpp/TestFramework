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

class TestMacrosFormatter
{
public:
    template <typename V, typename R>
    static std::string FormatComparison(const V& value, const R& reference);

private:
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
};

template <typename V, typename R>
std::string TestMacrosFormatter::FormatComparison(const V& value, const R& reference)
{
    std::string formattedValue;
    std::string formattedReference;
    UniversalFormatter<std::decay<V>::type>::Format(value, formattedValue);
    UniversalFormatter<std::decay<R>::type>::Format(reference, formattedReference);

    return (formattedValue + " != " + formattedReference);
}

template <typename T, typename Enable>
bool TestMacrosFormatter::UniversalFormatter<T, Enable>::Format(const T& value, std::string& output)
{
    return false;
}

template <typename T>
bool TestMacrosFormatter::UniversalFormatter<T, typename std::enable_if<std::is_integral<T>::value>::type>::Format(T value, std::string& output)
{
    output = std::to_string(value);
    return true;
}

template <typename T>
bool TestMacrosFormatter::UniversalFormatter<T, typename std::enable_if<!std::is_integral<T>::value && std::is_convertible<T, int>::value>::type>::Format(T value, std::string& output)
{
    output = std::to_string(value);
    return true;
}

}
}

#endif
