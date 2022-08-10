/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTFRAMEWORKERRORCATEGORY_HPP
#define GUARD_ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTFRAMEWORKERRORCATEGORY_HPP

#include <Ishiko/Errors.hpp>

namespace Ishiko
{

class TestFrameworkErrorCategory : public Ishiko::ErrorCategory
{
public:
    enum class Value
    {
        generic_error = -1
    };

    static const TestFrameworkErrorCategory& Get() noexcept;

    const char* name() const noexcept override;
    std::ostream& streamOut(int value, std::ostream& os) const override;

private:
    TestFrameworkErrorCategory() noexcept = default;
};

void Throw(TestFrameworkErrorCategory::Value value, const char* file, int line);
void Fail(TestFrameworkErrorCategory::Value value, Error& error) noexcept;

}

#endif
