/*
    Copyright (c) 2007-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/TestFramework/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_TEST_TESTFRAMEWORK_CORE_TESTENVIRONMENTTESTS_TESTENVIRONMENTTESTS_H_
#define _ISHIKO_TEST_TESTFRAMEWORK_CORE_TESTENVIRONMENTTESTS_TESTENVIRONMENTTESTS_H_

#include "Ishiko/TestFramework/TestFrameworkCore.h"

class TestEnvironmentTests : public Ishiko::Tests::TestSequence
{
public:
    TestEnvironmentTests(const Ishiko::Tests::TestNumber& number,
        const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
    static void ConstructorTest2(Ishiko::Tests::Test& test);
    static void ConstructorTest3(Ishiko::Tests::Test& test);
    static void GetTestDataDirectoryTest1(Ishiko::Tests::Test& test);
    static void GetTestDataDirectoryTest2(Ishiko::Tests::Test& test);
    static void GetTestDataDirectoryTest3(Ishiko::Tests::Test& test);
    static void GetTestDataPathTest1(Ishiko::Tests::Test& test);
    static void SetTestDataDirectoryTest1(Ishiko::Tests::Test& test);
    static void GetReferenceDataDirectoryTest1(Ishiko::Tests::Test& test);
    static void SetReferenceDataDirectoryTest1(Ishiko::Tests::Test& test);
    static void GetTestOutputDirectoryTest1(Ishiko::Tests::Test& test);
    static void SetTestOutputDirectoryTest1(Ishiko::Tests::Test& test);
};

#endif
