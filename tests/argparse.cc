#include <string>

#include <gtest/gtest.h>

#include "exception.hh"
#include "argument.hh"

using namespace argparse;

/////////////////////
///// Test exceptions
/////////////////////
TEST (argparse_exception, what) { 
    argparse_exception e("msg1");
    ASSERT_EQ(std::string(e.what()), std::string("msg1"));
}

TEST (parse_exception, what) { 
    parse_exception e("msg1");
    ASSERT_EQ(std::string(e.what()), std::string("msg1"));
}

TEST (invalid_argument_exception, what) { 
    invalid_argument_exception e("msg1");
    ASSERT_EQ(std::string(e.what()), std::string("msg1"));
}

TEST (required_argument_exception, what) { 
    required_argument_exception e("msg1");
    ASSERT_EQ(std::string(e.what()), std::string("msg1"));
}


/////////////////////
///// Arguments
/////////////////////
TEST (argument, default_value) {
    argument arg1 {"--foo", "-f" };

    // No default value set, you could change
    // has_value wathever you want
    arg1.has_value(false);
    arg1.has_value(true);
    arg1.has_value(false);
    try
    {
        // has_value() was set false, set a default value is an error
        arg1.default_value("bar");
        FAIL();
    }
    catch (const invalid_argument_exception& ex)
    {
    }
    catch (...)
    {
        FAIL();
    }
}

TEST (argument, has_value) {
    argument arg1 {"--foo", "-f" };

    arg1.default_value("bar");
    arg1.has_value(true);
    arg1.default_value("deadbeef");
    try
    {
        // Default value is set, you can remove
        arg1.has_value(false);
        FAIL();
    }
    catch (const invalid_argument_exception& ex)
    {
    }
    catch (...)
    {
        FAIL();
    }
}

/////////////////////
///// Main
/////////////////////
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

