#include "triangle.h"
#include "vector.h"
#include "catch.hpp"
#include <math.h>

SCENARIO("A triangle normal vector can be calculated","[square_matrix]") {

    GIVEN("A triangle lying on the XY plane") {
        Triangle t(
            Vertex(2.0f, 3.0f, 0.0f),
            Vertex(5.0f, 10.0f, 0.0f),
            Vertex(1.0f, 1.0f, 0.0f)
        );

        WHEN("The normal is calculated") {
            Vector norm = t.normal();

            THEN("The normal is the Z axis") {
                INFO("x:" << norm[0]);
                INFO("y:" << norm[1]);
                INFO("z:" << norm[2]);
                REQUIRE(norm[0] == 0.0f);
                REQUIRE(norm[1] == 0.0f);
                REQUIRE(norm[2] == 1.0f);
            }
        }
    }
}