#include "add.h"
#include "catch.hpp"

TEST_CASE("add 2 and 3", "[Add]")
{
    REQUIRE(add(2, 3) == 4);
}

TEST_CASE("add 2 and 2", "[Add]")
{
    REQUIRE(add(2, 2) == 4);
}
