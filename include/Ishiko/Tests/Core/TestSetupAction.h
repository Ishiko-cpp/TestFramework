/*
    Copyright (c) 2015-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_CORE_TESTSETUPACTION_H_
#define _ISHIKO_TESTS_CORE_TESTSETUPACTION_H_

namespace Ishiko
{
namespace Tests
{

/// Base class that represents an action that needs to be performed before the test is run.

/// This class does nothing. Derived classes can override the run() method to perform
/// the required action.
class TestSetupAction
{
public:
    TestSetupAction();
    virtual ~TestSetupAction();

    /// This method is called to perform the setup action.
    virtual void setup();
};

}
}

#endif
