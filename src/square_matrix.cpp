#include "square_matrix.h"

#include "vector.h"
#include <assert.h>
#include <cmath>

SquareMatrix::SquareMatrix() {
    // Construct an empty matrix
    values = vector< vector<float> >();
}

SquareMatrix::SquareMatrix(int size) : SquareMatrix() {
    // Construct a matrix with given values
    for (int r = 0; r < size; ++r) {
        vector<float> row = vector<float>();
        for (int c = 0; c < size; ++c) {
            row.push_back(0.0f);
        }
        values.push_back(row);
    }
}

SquareMatrix::SquareMatrix(vector< vector<float> > values) {
    // Construct a matrix with given values
    this->values = values;
}

SquareMatrix SquareMatrix::identity(int size) {
    // Construct the identity matrix of given size
    SquareMatrix m = SquareMatrix(size);
    for (int i = 0; i < size; ++i) {
        m(i,i) = 1;
    }
    return m;
}

SquareMatrix::SquareMatrix(const SquareMatrix& m) : SquareMatrix(m.dimensions()) {
    // Copy constructor
    for (int row = 0; row < m.dimensions(); ++row) {
        for (int column = 0; column < m.dimensions(); ++column) {
            values[row][column] = m(row,column);
        }
    }
}

SquareMatrix SquareMatrix::applyComponentWiseOperation(auto operation) const {
    SquareMatrix m = SquareMatrix(*this);
    for (int row = 0; row < dimensions(); ++row) {
        for (int column = 0; column < dimensions(); ++column) {
            m(row,column) = operation(row, column);
        }
    }
    return m;
}

SquareMatrix SquareMatrix::operator-() const {
    // Matrix negation
    auto negate = [&] (int i, int j) {return -values[i][j];};
    return applyComponentWiseOperation(negate);
}

SquareMatrix SquareMatrix::operator+(const SquareMatrix& m) const {
    // Matrix addition
    assert(dimensions() == m.dimensions());
    auto add = [&] (int i, int j) {return values[i][j] + m(i,j);};
    return applyComponentWiseOperation(add);
}

SquareMatrix SquareMatrix::operator-(const SquareMatrix& m) const {
    // Matrix subtraction
    assert(dimensions() == m.dimensions());
    auto subtract = [&] (int i, int j) {return values[i][j] - m(i,j);};
    return applyComponentWiseOperation(subtract);
}

SquareMatrix SquareMatrix::operator*(float scalar) const {
    // Multiplication by scalar
    auto multiply = [&] (int i, int j) {return values[i][j] * scalar;};
    return applyComponentWiseOperation(multiply);
}

SquareMatrix SquareMatrix::operator/(float scalar) const {
    // Division by scalar
    auto divide = [&] (int i, int j) {return values[i][j] / scalar;};
    return applyComponentWiseOperation(divide);
}

SquareMatrix SquareMatrix::operator*(const SquareMatrix& m) const {
    // Multiplication by matrix
    assert(dimensions() == m.dimensions());    
    auto multiply = [&] (int i, int j) {return Vector::dot(row(i),m.column(j));};
    return applyComponentWiseOperation(multiply);
}

SquareMatrix SquareMatrix::transpose() const {
    // Matrix transpose
    auto transpose = [&] (int i, int j) {return values[j][i];};
    return applyComponentWiseOperation(transpose);
}

// Helper functions to help calculate determinant and inverse.

SquareMatrix SquareMatrix::subMatrix(int i, int j) const {
    // Derive a size n-1 matrix by deleting the ith row and jth column
    // Helper to calculate the determinant
    SquareMatrix m = SquareMatrix(dimensions() - 1);
    for (int row = 0; row < dimensions(); ++row) {
        for (int column = 0; column < dimensions(); ++column) {
            if(i != row && j != column) {
                int newRowIndex = row > i ? row - 1 : row;
                int newColumnIndex = column > j ? column - 1 : column;
                m(newRowIndex,newColumnIndex) = values[row][column];
            }
        }
    }
    return m;
}

float SquareMatrix::pureDeterminant() const {
    // Matrix determinant without using cofactor matrix
    // assert(dimensions() < 4);
    if(dimensions() == 1) {
        return values[0][0];
    } else {
        float result = 0;
        for (int j = 0; j < dimensions(); ++j) {
            result += pow(-1,j+2) * subMatrix(0, j).pureDeterminant() * values[0][j];
        }
        return result;
    }
}

void SquareMatrix::computeCofactorMatrix() const {
    // Precompute the cofactor matrix to make finding the determinant
    // of the whole matrix more efficient if the inverse has already been
    // found (or vice versa).
    // Cofactors are for transposed matrix.
    if(cofactorsAreStale) {
        if(cofactors == NULL) {
            cofactors = unique_ptr<SquareMatrix>(new SquareMatrix(dimensions()));
        }
        for (int i = 0; i < dimensions(); ++i) {
            for (int j = 0; j < dimensions(); ++j) {
                (*cofactors)(j,i) = pow(-1,i+j+2) * subMatrix(i, j).pureDeterminant();
            }
        }
        cofactorsAreStale = false;
    }
}

float SquareMatrix::determinant() const {
    // Matrix determinant
    if(dimensions() == 1) {
        return values[0][0];
    } else {
        // First compute the cofactor matrix
        computeCofactorMatrix();
        // Use the cofactor matrix to compute the determinant
        float result = 0;
        for (int j = 0; j < dimensions(); ++j) {
            result += (*cofactors)(j,0) * values[0][j];
        }
        return result;
    }
}

SquareMatrix SquareMatrix::inverse() const {
    // Matrix inverse
    computeCofactorMatrix();
    int det = determinant();
    // Matrix is invertible iff determinant is not zero
    assert(det != 0);
    return (*cofactors) / det;
}

int SquareMatrix::dimensions() const {
    // Get number of dimensions of matrix
    return (int)values.size();
}

Vector SquareMatrix::column(int index) const {
    // Get a column as vector
    Vector v = Vector(dimensions());
    for (int row = 0; row < dimensions(); ++row) {
        v[row] = values[row][index];
    }
    return v;
}

Vector SquareMatrix::row(int index) const {
    // Get a row as vector
    return Vector(values[index]);
}

float& SquareMatrix::operator()(int row, int column) {
    // Element access
    cofactorsAreStale = true;
    return values[row][column];
}

float SquareMatrix::operator()(int row, int column) const {
    // Element access
    return values[row][column];
}
