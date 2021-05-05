#pragma once

#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

class Vector;

class SquareMatrix {
    public:
        // Construct a empty matrix
        SquareMatrix();
        // Construct a zero square matrix with given size
        SquareMatrix(int width);
        // Construct a matrix with given 2D vector
        SquareMatrix(std::vector< std::vector<float> > values);
        // Construct a matrix of given width populated with given values
        SquareMatrix(int width, std::vector<float> values);
        // Construct the identity matrix of given size
        static SquareMatrix identity(int width);
        // Copy constructor
        SquareMatrix(const SquareMatrix& m);
        // Assignment operators
        SquareMatrix& operator=(SquareMatrix m);
        SquareMatrix& operator+=(const SquareMatrix& m);
        SquareMatrix& operator-=(const SquareMatrix& m);
        SquareMatrix& operator*=(const SquareMatrix& m);
        SquareMatrix& operator*=(float scalar);
        SquareMatrix& operator/=(float scalar);
        // Matrix negation
        SquareMatrix operator-() const;
        // Multiplication by vector
        Vector operator*(const Vector& v) const;
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
        friend void swap(SquareMatrix& first, SquareMatrix& second) noexcept {
            using std::swap;
            swap(first.values, second.values);
            swap(first.cofactors, second.cofactors);
            swap(first.cofactorsAreStale, second.cofactorsAreStale);
        }
    private:
        // Apply an operation to every element of the matrix
        void applyComponentWiseOperation(auto operation);
        // Return the matrix given by removing row i and column j
        SquareMatrix subMatrix(int i, int j) const;
        // Calculate the determinant recursively without using the cofactor matrix
        float pureDeterminant() const;
        // Compute the matrix of cofactors for this matrix
        void computeCofactorMatrix() const;
        // Actual elements of the matrix
        std::vector< std::vector<float> > values;
        // Cofactor matrix
        mutable std::unique_ptr<SquareMatrix> cofactors = NULL;
        // Judge whether cofactors need to be recalculated
        mutable bool cofactorsAreStale = true;
};

// Matrix addition
inline SquareMatrix operator+(SquareMatrix m, const SquareMatrix& n) {
    m += n;
    return m;
};
// Matrix subtraction
inline SquareMatrix operator-(SquareMatrix m, const SquareMatrix& n) {
    m -= n;
    return m;
}
// Multiplication by scalar
inline SquareMatrix operator*(SquareMatrix m, float scalar) {
    m *= scalar;
    return m;
};
// Commutativity for multiplying by scalar
inline SquareMatrix operator*(float f, SquareMatrix m) {
    return m * f;
}
// Division by scalar
inline SquareMatrix operator/(SquareMatrix m, float scalar) {
    m /= scalar;
    return m;
}
// Multiplication by matrix
inline SquareMatrix operator*(SquareMatrix m, const SquareMatrix& n) {
    m *= n;
    return m;
}