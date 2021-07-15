/*
    Copyright (c) 2015-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/tests/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_TESTS_CORE_TESTTEARDOWNACTION_H_
#define _ISHIKO_TESTS_CORE_TESTTEARDOWNACTION_H_

namespace Ishiko
{
namespace Tests
{

/// Base class that represents an action that needs to be performed after the test has been run.

/// This class does nothing. Derived classes can override the run() method to perform
/// the required action.
class TestTeardownAction
{
public:
    TestTeardownAction();
    virtual ~TestTeardownAction();

    /// This method is called to perform the teardown action.
    virtual void teardown();
};

}
}

#endif
