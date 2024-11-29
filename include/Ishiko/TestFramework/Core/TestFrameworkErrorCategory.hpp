// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

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
    const char* message(int ev, char* buffer, size_t len) const noexcept override;

private:
    TestFrameworkErrorCategory() noexcept = default;
};

void Throw(TestFrameworkErrorCategory::Value value, const char* file, int line);
void Fail(TestFrameworkErrorCategory::Value value, Error& error) noexcept;

}

#endif
