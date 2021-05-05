#include "square_matrix.h"
#include "vector.h"
#include "catch.hpp"
#include <math.h>

SCENARIO("A square matrix can be transposed","[square_matrix]") {

    GIVEN("A square matrix M") {
        SquareMatrix M(3, std::vector<float>({
            3.23f, 4.54f, 29.3f,
            2.33f, 328.3f, 23.339f,
            9.0f, 23.2f, 299.12f
        }));

        WHEN("M is transposed") {
            SquareMatrix MT = M.transpose();

            THEN("M is correctly transposed") {
                REQUIRE(MT(0,0) == 3.23f);
                REQUIRE(MT(0,1) == 2.33f);
                REQUIRE(MT(0,2) == 9.0f);
                REQUIRE(MT(1,0) == 4.54f);
                REQUIRE(MT(1,1) == 328.3f);
                REQUIRE(MT(1,2) == 23.2f);
                REQUIRE(MT(2,0) == 29.3f);
                REQUIRE(MT(2,1) == 23.339f);
                REQUIRE(MT(2,2) == 299.12f);
            }
        }
    }
}

SCENARIO("A square matrix can be multiplied by a scalar","[square_matrix]") {

    GIVEN("A square matrix M and a scalar s") {
        SquareMatrix M(3, std::vector<float>({
            3.23f, 4.54f, 29.3f,
            2.33f, 328.3f, 23.339f,
            9.0f, 23.2f, 299.12f
        }));
        float s = 2.0f;

        WHEN("M is multiplied by s") {
            SquareMatrix Ms = M * s;

            THEN("M is correctly multiplied by s") {
                REQUIRE(Ms(0,0) == Approx(6.46f));
                REQUIRE(Ms(0,1) == Approx(9.08f));
                REQUIRE(Ms(0,2) == Approx(58.6f));
                REQUIRE(Ms(1,0) == Approx(4.66f));
                REQUIRE(Ms(1,1) == Approx(656.6f));
                REQUIRE(Ms(1,2) == Approx(46.678f));
                REQUIRE(Ms(2,0) == Approx(18.0f));
                REQUIRE(Ms(2,1) == Approx(46.4f));
                REQUIRE(Ms(2,2) == Approx(598.24f));
            }
        }

        WHEN("s is multiplied by M") {
            SquareMatrix sM = s * M;

            THEN("M is correctly multiplied by s") {
                REQUIRE(sM(0,0) == Approx(6.46f));
                REQUIRE(sM(0,1) == Approx(9.08f));
                REQUIRE(sM(0,2) == Approx(58.6f));
                REQUIRE(sM(1,0) == Approx(4.66f));
                REQUIRE(sM(1,1) == Approx(656.6f));
                REQUIRE(sM(1,2) == Approx(46.678f));
                REQUIRE(sM(2,0) == Approx(18.0f));
                REQUIRE(sM(2,1) == Approx(46.4f));
                REQUIRE(sM(2,2) == Approx(598.24f));
            }
        }
    }
}

SCENARIO("A square matrix M can be added to or subtracted from another matrix","[square_matrix]") {
    SquareMatrix M(3, std::vector<float>({
        3.23f, 4.54f, 29.3f,
        2.33f, 328.3f, 23.339f,
        9.0f, 23.2f, 299.12f
    }));

    GIVEN("Another square matrix N") {
        SquareMatrix N(3, std::vector<float>({
            0.0f, 1.1f, 2.2f,
            2.33f, 7.43f, 0.0f,
            9.0f, 0.0f, 2.9f
        }));

        WHEN("M is added to N") {
            SquareMatrix MN = M + N;

            THEN("M is correctly added to N") {
                REQUIRE(MN(0,0) == Approx(3.23f));
                REQUIRE(MN(0,1) == Approx(5.64f));
                REQUIRE(MN(0,2) == Approx(31.5f));
                REQUIRE(MN(1,0) == Approx(4.66f));
                REQUIRE(MN(1,1) == Approx(335.73f));
                REQUIRE(MN(1,2) == Approx(23.339f));
                REQUIRE(MN(2,0) == Approx(18.0f));
                REQUIRE(MN(2,1) == Approx(23.2f));
                REQUIRE(MN(2,2) == Approx(302.02f));
            }
        }

        WHEN("N is added to M") {
            SquareMatrix NM = N + M;

            THEN("M is correctly added to N") {
                REQUIRE(NM(0,0) == Approx(3.23f));
                REQUIRE(NM(0,1) == Approx(5.64f));
                REQUIRE(NM(0,2) == Approx(31.5f));
                REQUIRE(NM(1,0) == Approx(4.66f));
                REQUIRE(NM(1,1) == Approx(335.73f));
                REQUIRE(NM(1,2) == Approx(23.339f));
                REQUIRE(NM(2,0) == Approx(18.0f));
                REQUIRE(NM(2,1) == Approx(23.2f));
                REQUIRE(NM(2,2) == Approx(302.02f));
            }
        }

        WHEN("M is subtracted from N") {
            SquareMatrix NM = N - M;

            THEN("M is correctly subtracted from N") {
                REQUIRE(NM(0,0) == Approx(-3.23f));
                REQUIRE(NM(0,1) == Approx(-3.44f));
                REQUIRE(NM(0,2) == Approx(-27.1f));
                REQUIRE(NM(1,0) == Approx(0.0f));
                REQUIRE(NM(1,1) == Approx(-320.87f));
                REQUIRE(NM(1,2) == Approx(-23.339f));
                REQUIRE(NM(2,0) == Approx(0.0f));
                REQUIRE(NM(2,1) == Approx(-23.2f));
                REQUIRE(NM(2,2) == Approx(-296.22f));
            }
        }

        WHEN("N Is subtracted from M") {
            SquareMatrix MN = M - N;

            THEN("N is correctly subtracted from M") {
                REQUIRE(MN(0,0) == Approx(3.23f));
                REQUIRE(MN(0,1) == Approx(3.44f));
                REQUIRE(MN(0,2) == Approx(27.1f));
                REQUIRE(MN(1,0) == Approx(0.0f));
                REQUIRE(MN(1,1) == Approx(320.87f));
                REQUIRE(MN(1,2) == Approx(23.339f));
                REQUIRE(MN(2,0) == Approx(0.0f));
                REQUIRE(MN(2,1) == Approx(23.2f));
                REQUIRE(MN(2,2) == Approx(296.22f));
            }
        }
    }
}

SCENARIO("A square matrix M can be multiplied by another matrix","[square_matrix]") {
    SquareMatrix M(3, std::vector<float>({
        3.23f, 4.54f, 29.3f,
        2.33f, 328.3f, 23.339f,
        9.0f, 23.2f, 299.12f
    }));

    GIVEN("Another square matrix N") {
        SquareMatrix N(3, std::vector<float>({
            0.0f, 1.1f, 2.2f,
            2.33f, 7.43f, 0.0f,
            9.0f, 0.0f, 2.9f
        }));

        WHEN("M is multiplied by N") {
            SquareMatrix MN = M * N;

            THEN("M is correctly multiplied by N") {
                REQUIRE(MN(0,0) == Approx(274.278f));
                REQUIRE(MN(0,1) == Approx(37.2852f));
                REQUIRE(MN(0,2) == Approx(92.076f));
                REQUIRE(MN(1,0) == Approx(974.99f));
                REQUIRE(MN(1,1) == Approx(2441.83f));
                REQUIRE(MN(1,2) == Approx(72.8091f));
                REQUIRE(MN(2,0) == Approx(2746.14f));
                REQUIRE(MN(2,1) == Approx(182.276f));
                REQUIRE(MN(2,2) == Approx(887.248f));
            }
        }

        WHEN("N is multiplied by M") {
            SquareMatrix NM = N * M;

            THEN("N is correctly multiplied by M") {
                REQUIRE(NM(0,0) == Approx(22.363f));
                REQUIRE(NM(0,1) == Approx(412.17f));
                REQUIRE(NM(0,2) == Approx(683.737f));
                REQUIRE(NM(1,0) == Approx(24.8378f));
                REQUIRE(NM(1,1) == Approx(2449.85f));
                REQUIRE(NM(1,2) == Approx(241.678f));
                REQUIRE(NM(2,0) == Approx(55.17f));
                REQUIRE(NM(2,1) == Approx(108.14f));
                REQUIRE(NM(2,2) == Approx(1131.15f));
            }
        }
    }

    GIVEN("The identity matrix I") {
        SquareMatrix I = SquareMatrix::identity(3);

        WHEN("M is multipied by I") {
            SquareMatrix MI = M * I;

            THEN("The result is M") {
                REQUIRE(MI(0,0) == M(0,0));
                REQUIRE(MI(0,1) == M(0,1));
                REQUIRE(MI(0,2) == M(0,2));
                REQUIRE(MI(1,0) == M(1,0));
                REQUIRE(MI(1,1) == M(1,1));
                REQUIRE(MI(1,2) == M(1,2));
                REQUIRE(MI(2,0) == M(2,0));
                REQUIRE(MI(2,1) == M(2,1));
                REQUIRE(MI(2,2) == M(2,2));
            }
        }

        WHEN("I is multiplied by M") {
            SquareMatrix IM = I * M;

            THEN("The result is M") {
                REQUIRE(IM(0,0) == M(0,0));
                REQUIRE(IM(0,1) == M(0,1));
                REQUIRE(IM(0,2) == M(0,2));
                REQUIRE(IM(1,0) == M(1,0));
                REQUIRE(IM(1,1) == M(1,1));
                REQUIRE(IM(1,2) == M(1,2));
                REQUIRE(IM(2,0) == M(2,0));
                REQUIRE(IM(2,1) == M(2,1));
                REQUIRE(IM(2,2) == M(2,2));
            }
        }
    }
}

SCENARIO("A square matrix M can be multiplied by a vector","[square_matrix]") {
    SquareMatrix M(3, std::vector<float>({
        3.23f, 4.54f, 29.3f,
        2.33f, 328.3f, 23.339f,
        9.0f, 23.2f, 299.12f
    }));

    GIVEN("A vector V") {
        std::vector<float> ordinary_values = {2.453f, 4.234f, 3.098f};
        Vector V(ordinary_values);

        WHEN("M is multiplied by V") {
            Vector MV = M * V;

            THEN("M is correctly multiplied by V") {
                REQUIRE(MV[0] == Approx(117.917f));
                REQUIRE(MV[1] == Approx(1468.04f));
                REQUIRE(MV[2] == Approx(1046.98f));
            }
        }
    }
}

SCENARIO("A square matrix can be inverted","[square_matrix]") {
    
    GIVEN("A square matrix M") {
        SquareMatrix M(3, std::vector<float>({
            3.23f, 4.54f, 29.3f,
            2.33f, 328.3f, 23.339f,
            9.0f, 23.2f, 299.12f
        }));

        WHEN("M is inverted") {
            SquareMatrix invM = M.inverse();

            THEN("M is correctly inverted") {
                REQUIRE(invM(0,0) == Approx(0.427879f));
                REQUIRE(invM(0,1) == Approx(-0.00297161f));
                REQUIRE(invM(0,2) == Approx(-0.0416806f));
                REQUIRE(invM(1,0) == Approx(-0.00213326f));
                REQUIRE(invM(1,1) == Approx(0.0030777f));
                REQUIRE(invM(1,2) == Approx(-0.0000311774f));
                REQUIRE(invM(2,0) == Approx(-0.0127087f));
                REQUIRE(invM(2,1) == Approx(-0.000149298f));
                REQUIRE(invM(2,2) == Approx(0.00459965f));
            }
        }

        WHEN("M is inverted, a value is changed and then it is inverted again") {
            SquareMatrix invM = M.inverse();
            M(1,1) = 30.0f;
            invM = M.inverse();

            THEN("M is correctly inverted") {
                REQUIRE(invM(0,0) == Approx(0.450962f));
                REQUIRE(invM(0,1) == Approx(-0.0362734f));
                REQUIRE(invM(0,2) == Approx(-0.0413432f));
                REQUIRE(invM(1,0) == Approx(-0.02604f));
                REQUIRE(invM(1,1) == Approx(0.0375684f));
                REQUIRE(invM(1,2) == Approx(-0.000380571f));
                REQUIRE(invM(2,0) == Approx(-0.011549f));
                REQUIRE(invM(2,1) == Approx(-0.00182243f));
                REQUIRE(invM(2,2) == Approx(0.0046166f));
            }           
        }
    }
}

SCENARIO("A square matrix has a determinant","[square_matrix]") {
    
    GIVEN("A square matrix M") {
        SquareMatrix M(3, std::vector<float>({
            3.23f, 4.54f, 29.3f,
            2.33f, 328.3f, 23.339f,
            9.0f, 23.2f, 299.12f
        }));

        WHEN("The determinant of M is calculated") {
            float det = M.determinant();

            THEN("The determinant is correctly calculated") {
                REQUIRE(det == Approx(228241.219932f));
            }
        }

        WHEN("The determinant of M is calculated, M is modified and then the determinant is recalculated") {
            float det = M.determinant();
            M(1,1) = 0.0f;
            det = M.determinant();

            THEN("The determinant is correctly calculated") {
                REQUIRE(det == Approx(-2375.610148f));
            }
        }
    }
}