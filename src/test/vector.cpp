#include "vector.h"
#include "catch.hpp"

TEST_CASE("Create an empty vector") {
    Vector v;
    REQUIRE(v.dimensions() == 0);
}