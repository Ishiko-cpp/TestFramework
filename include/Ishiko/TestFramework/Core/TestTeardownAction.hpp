/*
    Copyright (c) 2015-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTTEARDOWNACTION_HPP_
#define _ISHIKO_CPP_TESTFRAMEWORK_CORE_TESTTEARDOWNACTION_HPP_

namespace Ishiko
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

#endif
