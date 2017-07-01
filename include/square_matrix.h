#pragma once

#include "vector.h"
#include <vector>
#include <memory>

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
        // Matrix determinant
        float determinant() const;
        // Matrix inverse
        SquareMatrix inverse() const;
        // Get number of dimensions of matrix
        int dimensions() const;
        // Get a column as vector
        Vector column(int index) const;
        // Get a row as vector
        Vector row(int index) const;
        // Element access
        float& operator()(int row, int column);
        float operator()(int row, int column) const;
    private:
        // Apply an operation to every element of the matrix
        SquareMatrix applyComponentWiseOperation(auto operation) const;
        // Return the matrix given by removing row i and column j
        SquareMatrix subMatrix(int i, int j) const;
        // Calculate the determinant recursively without using the cofactor matrix
        float pureDeterminant() const;
        // Compute the matrix of cofactors for this matrix
        void computeCofactorMatrix() const;
        // Actual elements of the matrix
        vector< vector<float> > values;
        // Cofactor matrix
        mutable unique_ptr<SquareMatrix> cofactors = NULL;
        // Judge whether cofactors need to be recalculated
        mutable bool cofactorsAreStale = true;
};