/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include "TestFrameworkErrorCategory.hpp"

using namespace Ishiko;

const TestFrameworkErrorCategory& TestFrameworkErrorCategory::Get() noexcept
{
    static TestFrameworkErrorCategory theCategory;
    return theCategory;
}

const char* TestFrameworkErrorCategory::name() const noexcept
{
    return "Ishiko::TestFrameworkErrorCategory";
}

std::ostream& TestFrameworkErrorCategory::streamOut(int value, std::ostream& os) const
{
    switch (static_cast<Value>(value))
    {
    case Value::generic_error:
        os << "generic error";
        break;

    default:
        os << "unknown value";
        break;
    }
    return os;
}

void Ishiko::Throw(TestFrameworkErrorCategory::Value value, const char* file, int line)
{
    throw Exception(static_cast<int>(value), TestFrameworkErrorCategory::Get(), file, line);
}

void Ishiko::Fail(TestFrameworkErrorCategory::Value value, Error& error) noexcept
{
    error.fail(TestFrameworkErrorCategory::Get(), static_cast<int>(value));
}
