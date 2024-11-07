// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTSETUPACTION_HPP
#define GUARD_ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTSETUPACTION_HPP

namespace Ishiko
{
    class Test;

    /// Base class that represents an action that needs to be performed before the test is run.

    /// This class does nothing. Derived classes can override the run() method to perform
    /// the required action.
    class TestSetupAction
    {
    public:
        TestSetupAction();
        virtual ~TestSetupAction();

        /// This method is called to perform the setup action.
        virtual void setup(const Test& test);
    };
}

#endif
