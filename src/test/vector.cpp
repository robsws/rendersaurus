#include "vector.h"
#include "catch.hpp"
#include <math.h>

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
                REQUIRE(minusZ[0] == 0.0f);
                REQUIRE(minusZ[1] == 0.0f);
                REQUIRE(minusZ[2] == 0.0f);
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

SCENARIO("Vector magnitude (length) can be calculated", "[vector]") {
    GIVEN("A standard vector V of float values") {
        vector<float> ordinary_values = {2.453f, 4.234f, 3.098f};
        Vector V(ordinary_values);

        WHEN("Magnitude m of V is calculated") {
            float m = V.magnitude();

            THEN("Magnitude is correctly calculated") {
                REQUIRE(m == Approx(5.79150835275f));
            }
        }
    }

    GIVEN("A zero vector Z") {
        vector<float> zero_values = {0.0f, 0.0f, 0.0f};
        Vector Z(zero_values);
        REQUIRE(Z.dimensions() == 3);

        WHEN("Magnitude m of Z is calculated") {
            float m = Z.magnitude();

            THEN("m = 0") {
                REQUIRE(m == 0.0f);
            }
        }
    }
}

SCENARIO("A vector can be normalised to have unit length 1", "[vector]") {
    GIVEN("A standard vector V of float values") {
        vector<float> ordinary_values = {2.453f, 4.234f, 3.098f};
        Vector V(ordinary_values);

        WHEN("V is normalised") {
            Vector V1 = V.normalise();

            THEN("Vector is correctly normalised") {
                REQUIRE(V1[0] == Approx(0.423551f));
                REQUIRE(V1[1] == Approx(0.73107f));
                REQUIRE(V1[2] == Approx(0.534921f));
            }
        }
    }

    GIVEN("A zero vector Z") {
        vector<float> zero_values = {0.0f, 0.0f, 0.0f};
        Vector Z(zero_values);

        WHEN("Z is normalised") {
            Vector Z1 = Z.normalise();

            THEN("Vector components are NaN (division by zero)") {               
                REQUIRE(isnan(Z1[0]));
                REQUIRE(isnan(Z1[1]));
                REQUIRE(isnan(Z1[2]));
            }
        }
    }
}

SCENARIO("Dot product can be calculated between a vector V and another vector", "[vector]") {
    vector<float> ordinary_values1 = {2.453f, 4.234f, 3.098f};
    Vector V(ordinary_values1);

    GIVEN("Another vector W") {
        vector<float> ordinary_values2 = {35.324f, 2.922f, 82.829f};
        Vector W(ordinary_values2);

        WHEN("The dot product of V with W is taken") {
            float VW = Vector::dot(V, W);

            THEN("The dot product is calculated correctly") {
                REQUIRE(VW == Approx(355.625762f));
            }

            THEN("The result is the same as W dot V") {
                float WV = Vector::dot(W, V);
                REQUIRE(VW == Approx(WV));
            }
        }
    }

    GIVEN("A zero vector Z") {
        vector<float> zero_values = {0.0f, 0.0f, 0.0f};
        Vector Z(zero_values);

        WHEN("The dot product of V with Z is taken") {
            float VZ = Vector::dot(V, Z);

            THEN("The result is zero") {
                REQUIRE(VZ == 0.0f);
            }
        }
    }

    GIVEN("An identical vector") {

        WHEN("The dot product of V with V is taken") {
            float VV = Vector::dot(V, V);

            THEN("The result is the magnitude of V squared") {
                REQUIRE(VV == Approx(33.541569f));
            }
        }
    }
}

SCENARIO("Cross product can be calculated between a vector V and another vector", "[vector]") {
    vector<float> ordinary_values1 = {2.453f, 4.234f, 3.098f};
    Vector V(ordinary_values1);
    
    GIVEN("Another vector W") {
        vector<float> ordinary_values2 = {35.324f, 2.922f, 82.829f};
        Vector W(ordinary_values2);

        WHEN("The cross product of V with W is taken") {
            Vector VW = Vector::cross(V, W);

            THEN("The cross product is calculated correctly") {
                REQUIRE(VW[0] == Approx(341.646f));
                REQUIRE(VW[1] == Approx(-93.7458f));
                REQUIRE(VW[2] == Approx(-142.394f));
            }

        }
    }

    GIVEN("An identical vector") {

        WHEN("The cross product of V with V is taken") {
            Vector VV = Vector::cross(V, V);

            THEN("The result is the zero vector") {
                REQUIRE(VV[0] == 0.0f);
                REQUIRE(VV[1] == 0.0f);
                REQUIRE(VV[2] == 0.0f);
            }
        }
    }
}

SCENARIO("A vector V can be projected onto another vector", "[vector]") {
    vector<float> ordinary_values1 = {2.453f, 4.234f, 3.098f};
    Vector V(ordinary_values1);
    
    GIVEN("Another vector W") {
        vector<float> ordinary_values2 = {35.324f, 2.922f, 82.829f};
        Vector W(ordinary_values2);

        WHEN("V is projected onto W") {
            Vector VW = Vector::projection(V, W);

            THEN("The projection is calculated correctly") {
                REQUIRE(VW[0] == Approx(1.54764f));
                REQUIRE(VW[1] == Approx(0.128021f));
                REQUIRE(VW[2] == Approx(3.62896f));
            }

        }
    }

    GIVEN("A zero vector Z") {
        vector<float> zero_values = {0.0f, 0.0f, 0.0f};
        Vector Z(zero_values);

        WHEN("V is projected onto Z") {
            Vector VZ = Vector::projection(V, Z);

            THEN("The result is the undefined") {
                REQUIRE(isnan(VZ[0]));
                REQUIRE(isnan(VZ[1]));
                REQUIRE(isnan(VZ[2]));
            }
        }
    }

    GIVEN("An identical vector") {

        WHEN("V is projected onto V") {
            Vector VV = Vector::projection(V, V);

            THEN("The result is V") {
                REQUIRE(VV[0] == Approx(V[0]));
                REQUIRE(VV[1] == Approx(V[1]));
                REQUIRE(VV[2] == Approx(V[2]));
            }
        }
    }
}