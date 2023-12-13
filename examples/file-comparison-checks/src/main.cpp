/*
    Copyright (c) 2023 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/test-framework/blob/main/LICENSE.txt
*/

#include <Ishiko/TestFramework.hpp>
#include <boost/filesystem.hpp>
#include <fstream>

namespace
{
    void IdenticalFilesTest(Ishiko::Test& test)
    {
        boost::filesystem::path output_path = test.context().getOutputPath("TestFile1.txt");
        std::ofstream output_file{output_path.string()};
        output_file << "Hello World!" << std::endl;
        output_file.close();

        ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("TestFile1.txt");
        ISHIKO_TEST_PASS();
    }
}

int main(int argc, char* argv[])
{
    try
    {
        Ishiko::TestHarness::CommandLineSpecification command_line_spec;
        command_line_spec.setDefaultValue("context.data", "../../data");
        command_line_spec.setDefaultValue("context.output", "../../output");
        command_line_spec.setDefaultValue("context.reference", "../../reference");

        Ishiko::Configuration configuration = command_line_spec.createDefaultConfiguration();
        Ishiko::CommandLineParser::parse(command_line_spec, argc, argv, configuration);

        Ishiko::TestHarness the_test_harness("Ishiko/C++ TestFramework File Comparison Checks Example", configuration);

        Ishiko::TestSequence& the_tests = the_test_harness.tests();
        the_tests.append<Ishiko::Test>("IdenticalFilesTest", IdenticalFilesTest);

        return the_test_harness.run();
    }
    catch (const std::exception& e)
    {
        return Ishiko::TestApplicationReturnCode::exception;
    }
    catch (...)
    {
        return Ishiko::TestApplicationReturnCode::exception;
    }
}
