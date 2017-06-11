#pragma once

#include <vector>

using namespace std;

class SquareMatrix {
    public:
        // Construct a empty matrix
        SquareMatrix();
        // Construct a zero square matrix with given size
        SquareMatrix(int size);
        // Construct a matrix with given values
        SquareMatrix(vector< vector<float> > values);
        // Construct the identity matrix of given size
        static SquareMatrix identity(int size);
        // Copy constructor
        SquareMatrix(const SquareMatrix& m);
        // Matrix negation
        SquareMatrix operator-() const;
        // Matrix addition
        SquareMatrix operator+(const SquareMatrix& m) const;
        // Matrix subtraction
        SquareMatrix operator-(const SquareMatrix& m) const;
        // Multiplication by scalar
        SquareMatrix operator*(float scalar) const;
        // Division by scalar
        SquareMatrix operator/(float scalar) const;
        // Multiplication by matrix
        SquareMatrix operator*(const SquareMatrix& m) const;
        // Matrix transpose
        SquareMatrix transpose() const;
        // Matrix inverse
        SquareMatrix inverse() const;
        // Matrix determinant
        float determinant() const;
    private:
        SquareMatrix applyComponentWiseOperation(auto operation) const;
        vector< vector<float> > values;
}