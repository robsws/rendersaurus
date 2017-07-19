#include "vector.h"
#include "catch.hpp"

SCENARIO("Vectors can be multiplied by a scalar s", "[vector]") {
    float s = 5.693f;    

    GIVEN("A standard vector V of float values") {
        vector<float> ordinary_values = {2.453f, 4.234f, 3.098f};
        Vector V(ordinary_values);
        REQUIRE(V.dimensions() == 3);

        WHEN("V is multiplied by s") {
            Vector Vs = V*s;

            THEN("Vs = [sV1, sV2, sV3, ... ]") {
                REQUIRE(Vs[0] == 13.964929f);
                REQUIRE(Vs[1] == 24.104162f);
                REQUIRE(Vs[2] == 17.636914f);
            }
        }

        WHEN("s is multiplied by V") {
            Vector sV = s*V;

            THEN("sV = [sV1, sV2, sV3, ... ]") {
                REQUIRE(sV[0] == 13.964929f);
                REQUIRE(sV[1] == 24.104162f);
                REQUIRE(sV[2] == 17.636914f);
            }
        }
    }

    GIVEN("A zero vector Z") {
        vector<float> zero_values = {0.0f, 0.0f, 0.0f};
        Vector Z(zero_values);
        REQUIRE(Z.dimensions() == 3);

        WHEN("Z is multiplied by s") {
            Vector Zs = s*Z;            
            
            THEN("Zs = Z") {
                REQUIRE(Zs[0] == 0.0f);
                REQUIRE(Zs[1] == 0.0f);
                REQUIRE(Zs[2] == 0.0f);
            }
        }

        WHEN("s is multiplied by Z ") {
            Vector sZ = Z*s; 

            THEN("sZ = Z") {
                REQUIRE(sZ[0] == 0.0f);
                REQUIRE(sZ[1] == 0.0f);
                REQUIRE(sZ[2] == 0.0f);
            }
        }
    }
}

SCENARIO("Vectors can be negated", "[vector]") {

    GIVEN("A standard vector V of float values") {
        vector<float> ordinary_values = {2.453f, 4.234f, 3.098f};
        Vector V(ordinary_values);
        REQUIRE(V.dimensions() == 3);

        WHEN("V is negated") {
            Vector minusV = -V;

            THEN("-V = [-V1, -V2, -V3, ...]") {
                REQUIRE(minusV[0] == -2.453f);
                REQUIRE(minusV[1] == -4.234f);
                REQUIRE(minusV[2] == -3.098f);
            }
        }
    }

    GIVEN("A zero vector Z") {
        vector<float> zero_values = {0.0f, 0.0f, 0.0f};
        Vector Z(zero_values);
        REQUIRE(Z.dimensions() == 3);

        WHEN("Z is negated") {
            Vector minusZ = -Z;

            THEN("-Z = Z") {
                REQUIRE(minusZ[0] == -0.0f);
                REQUIRE(minusZ[1] == -0.0f);
                REQUIRE(minusZ[2] == -0.0f);
            }
        }
    }
}
/*
SCENARIO("Vectors can be added and subtracted from each other", "[vector]") {

}*/