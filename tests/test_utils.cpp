#include "doctest.h"
#include "utils.hpp"

TEST_SUITE_BEGIN("utils");

TEST_CASE("split()")
{
    std::string my_string = "Hi, I am a string";
    auto parts = Utils::split(my_string, " ");

    REQUIRE_FALSE(parts.empty());
    REQUIRE_EQ(parts.size(), 5);
    REQUIRE_EQ(parts[0], "Hi,");
    REQUIRE_EQ(parts[1], "I");
    REQUIRE_EQ(parts[2], "am");
    REQUIRE_EQ(parts[3], "a");
    REQUIRE_EQ(parts[4], "string");
}

TEST_SUITE_END();
