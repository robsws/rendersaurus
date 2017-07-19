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
                REQUIRE(Vs[0] == Approx(13.964929f));
                REQUIRE(Vs[1] == Approx(24.104162f));
                REQUIRE(Vs[2] == Approx(17.636914f));
            }
        }

        WHEN("s is multiplied by V") {
            Vector sV = s*V;

            THEN("sV = [sV1, sV2, sV3, ... ]") {
                REQUIRE(sV[0] == Approx(13.964929f));
                REQUIRE(sV[1] == Approx(24.104162f));
                REQUIRE(sV[2] == Approx(17.636914f));
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

SCENARIO("Scalar-vector multiplication is associative", "[vector]") {

    GIVEN("A vector V and two scalars {s,t}") {
        vector<float> ordinary_values = {2.453f, 4.234f, 3.098f};
        Vector V(ordinary_values);
        float s = 38.343f;
        float t = 95.342f;

        WHEN("(st)V") {
            Vector st_V = (s*t)*V;

            THEN("(st)V = s(tV)") {
                Vector s_tV = s*(t*V);
                REQUIRE(st_V[0] == Approx(s_tV[0]));
                REQUIRE(st_V[1] == Approx(s_tV[1]));
                REQUIRE(st_V[2] == Approx(s_tV[2]));
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

SCENARIO("Vectors can be added and subtracted from each other", "[vector]") {

    GIVEN("Two vectors {V, W}") {
        vector<float> ordinary_values1 = {2.453f, 4.234f, 3.098f};
        Vector V(ordinary_values1);
        vector<float> ordinary_values2 = {35.324f, 2.922f, 82.829f};
        Vector W(ordinary_values2);

        WHEN("V + W") {
            Vector VW = V + W;

            THEN("V + W = [V1+W1, V2+W2, V3+W3, ... ]") {
                REQUIRE(VW[0] == Approx(37.777f));
                REQUIRE(VW[1] == Approx(7.156f));
                REQUIRE(VW[2] == Approx(85.927f));
            }
        }

        WHEN("V - W") {
            Vector VW = V - W;

            THEN("V - W = [V1-W1, V2-W2, V3-W3, ... ]") {
                REQUIRE(VW[0] == Approx(-32.871f));
                REQUIRE(VW[1] == Approx(1.312f));
                REQUIRE(VW[2] == Approx(-79.731f));
            }
        }
    }
}

SCENARIO("Vector addition is commutative", "[vector]") {

    GIVEN("Two vectors {V, W}") {
        vector<float> ordinary_values1 = {2.453f, 4.234f, 3.098f};
        Vector V(ordinary_values1);
        vector<float> ordinary_values2 = {35.324f, 2.922f, 82.829f};
        Vector W(ordinary_values2);

        WHEN("V + W") {
            Vector VW = V + W;

            THEN("V + W = W + V") {
                Vector WV = W + V;
                REQUIRE(VW[0] == Approx(WV[0]));
                REQUIRE(VW[1] == Approx(WV[1]));
                REQUIRE(VW[2] == Approx(WV[2]));
            }
        }
    }
}

SCENARIO("Scalar-vector multiplication is distributive across addition and subtraction", "[vector]") {

    GIVEN("Two vectors {V,W} and a scalar s") {
        vector<float> ordinary_values1 = {2.453f, 4.234f, 3.098f};
        Vector V(ordinary_values1);
        vector<float> ordinary_values2 = {35.324f, 2.922f, 82.829f};
        Vector W(ordinary_values2);
        float s = 38.343f;

        WHEN("s(V + W)") {
            Vector s_VW = s * (V + W);

            THEN("s(V + W) = sV + sW") {
                Vector sV_sW = s * V + s * W;
                REQUIRE(s_VW[0] == Approx(sV_sW[0]));
                REQUIRE(s_VW[1] == Approx(sV_sW[1]));
                REQUIRE(s_VW[2] == Approx(sV_sW[2]));
            }
        }

        WHEN("s(V - W)") {
            Vector s_VW = s * (V - W);

            THEN("s(V - W) = sV - sW") {
                Vector sV_sW = s * V - s * W;
                REQUIRE(s_VW[0] == Approx(sV_sW[0]));
                REQUIRE(s_VW[1] == Approx(sV_sW[1]));
                REQUIRE(s_VW[2] == Approx(sV_sW[2]));
            }
        }
    }
}