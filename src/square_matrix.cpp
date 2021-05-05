#include "square_matrix.h"
#include "vector.h"
#include <assert.h>
#include <cmath>
#include <iostream>

SquareMatrix::SquareMatrix() {
    // Construct an empty matrix
    values = std::vector< std::vector<float> >();
}

SquareMatrix::SquareMatrix(int width) : SquareMatrix() {
    // Construct a matrix with given values
    for (int r = 0; r < width; ++r) {
        std::vector<float> row = std::vector<float>();
        for (int c = 0; c < width; ++c) {
            row.push_back(0.0f);
        }
        values.push_back(row);
    }
}

SquareMatrix::SquareMatrix(vector< vector<float> > values) {
    // Construct a matrix with given 2D vector
    this->values = values;
}

SquareMatrix::SquareMatrix(int width, std::vector<float> values) {
    // Construct a matrix of given size populated with given values
    assert(sqrt(values.size()) == width);
    std::vector< std::vector<float> > splitValues;
    for(int i = 0; i < width; ++i) {
        splitValues.push_back(std::vector<float>(values.begin() + i*width, values.begin() + (i+1)*width));
    }
    this->values = splitValues;
}

SquareMatrix SquareMatrix::identity(int width) {
    // Construct the identity matrix of given size
    SquareMatrix m = SquareMatrix(width);
    for (int i = 0; i < width; ++i) {
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

SquareMatrix& SquareMatrix::operator=(SquareMatrix m) {
    swap(*this, m);
    return *this;
}

void SquareMatrix::applyComponentWiseOperation(auto operation) {
    using std::swap;
    auto m = SquareMatrix(*this);
    for (int row = 0; row < dimensions(); ++row) {
        for (int column = 0; column < dimensions(); ++column) {
            m(row,column) = operation(row, column);
        }
    }
    swap(*this, m);
}

SquareMatrix SquareMatrix::operator-() const {
    // Matrix negation
    auto negate = [&] (int i, int j) {return -values[i][j];};
    SquareMatrix m = SquareMatrix(*this);
    m.applyComponentWiseOperation(negate);
    return m;
}

SquareMatrix& SquareMatrix::operator+=(const SquareMatrix& m) {
    // Matrix addition
    assert(dimensions() == m.dimensions());
    auto add = [&] (int i, int j) {return values[i][j] + m(i,j);};
    applyComponentWiseOperation(add);
    return *this;
}

SquareMatrix& SquareMatrix::operator-=(const SquareMatrix& m) {
    // Matrix subtraction
    assert(dimensions() == m.dimensions());
    auto subtract = [&] (int i, int j) {return values[i][j] - m(i,j);};
    applyComponentWiseOperation(subtract);
    return *this;
}

SquareMatrix& SquareMatrix::operator*=(float scalar) {
    // Multiplication by scalar
    auto multiply = [&] (int i, int j) {return values[i][j] * scalar;};
    applyComponentWiseOperation(multiply);
    return *this;
}

SquareMatrix& SquareMatrix::operator/=(float scalar) {
    // Division by scalar
    auto divide = [&] (int i, int j) {return values[i][j] / scalar;};
    applyComponentWiseOperation(divide);
    return *this;
}

SquareMatrix& SquareMatrix::operator*=(const SquareMatrix& m) {
    // Multiplication by matrix
    assert(dimensions() == m.dimensions());    
    auto multiply = [&] (int i, int j) {return dot(row(i),m.column(j));};
    applyComponentWiseOperation(multiply);
    return *this;
}

Vector SquareMatrix::operator*(const Vector& v) const {
    // Multiplication by vector
    assert(dimensions() == v.dimensions());
    Vector product = Vector(v);
    for(int i = 0; i < v.dimensions(); ++i) {
        product[i] = dot(this->row(i), v);
    }
    return product;
}

SquareMatrix SquareMatrix::transpose() const {
    // Matrix transpose
    auto transpose = [&] (int i, int j) {return values[j][i];};
    auto m = SquareMatrix(*this);
    m.applyComponentWiseOperation(transpose);
    return m;
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