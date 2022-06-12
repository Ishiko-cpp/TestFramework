/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTFRAMEWORKERRORCATEGORY_HPP_
#define _ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTFRAMEWORKERRORCATEGORY_HPP_

#include <Ishiko/Errors.hpp>

namespace Ishiko
{

class TestFrameworkErrorCategory : public Ishiko::ErrorCategory
{
public:
    enum class Value
    {
        generic = -1
    };

    static const TestFrameworkErrorCategory& Get() noexcept;

    const char* name() const noexcept override;

private:
    TestFrameworkErrorCategory() noexcept = default;
};

void Throw(TestFrameworkErrorCategory::Value value, const char* file, int line);
void Fail(Error& error, TestFrameworkErrorCategory::Value value) noexcept;

}

#endif
