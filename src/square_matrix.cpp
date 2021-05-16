#include "square_matrix.h"
#include "vector.h"
#include <assert.h>
#include <cmath>
#include <iostream>

SquareMatrix::SquareMatrix() :
	width(0),
	values(0) {
}

SquareMatrix::SquareMatrix(int width) : 
	width(width),
	values(width * width, 0.0f){
}

SquareMatrix::SquareMatrix(int width, float initValue) : 
	width(width),
    values(width * width, initValue){
}

SquareMatrix::SquareMatrix(int width, std::vector<float> values) :
    // Construct a matrix of given size populated with given values
	width(width),
    values(values) {
	assert(width * width == values.size());
}

SquareMatrix SquareMatrix::identity(int width){
    // Construct the identity matrix of given size
	SquareMatrix m(width);
	for (int i = 0; i < width; ++i) {
		m(i,i) = 1.0f;
	}
	return m;
}

SquareMatrix::SquareMatrix(const SquareMatrix& m) :
	width(m.width),
	values(m.values) {
    // Copy constructor
}

SquareMatrix& SquareMatrix::operator=(SquareMatrix m) {
    swap(*this, m);
    return *this;
}

float SquareMatrix::getValue(int i, int j) const {
	int index = i * this->width + j;
	return this->values[index];
}

float& SquareMatrix::getValue(int i, int j) {
	int index = i * this->width + j;
	return this->values[index];
}

template <typename F>
void SquareMatrix::applyComponentWiseOperation(F operation) {
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
    auto negate = [&] (int i, int j) {return -this->getValue(i,j);};
    SquareMatrix m = SquareMatrix(*this);
    m.applyComponentWiseOperation(negate);
    return m;
}

SquareMatrix& SquareMatrix::operator+=(const SquareMatrix& m) {
    // Matrix addition
    assert(dimensions() == m.dimensions());
    auto add = [&] (int i, int j) {return this->getValue(i, j) + m(i,j);};
    applyComponentWiseOperation(add);
    return *this;
}

SquareMatrix& SquareMatrix::operator-=(const SquareMatrix& m) {
    // Matrix subtraction
    assert(dimensions() == m.dimensions());
    auto subtract = [&] (int i, int j) {return this->getValue(i, j) - m(i,j);};
    applyComponentWiseOperation(subtract);
    return *this;
}

SquareMatrix& SquareMatrix::operator*=(float scalar) {
    // Multiplication by scalar
    auto multiply = [&] (int i, int j) {return this->getValue(i, j) * scalar;};
    applyComponentWiseOperation(multiply);
    return *this;
}

SquareMatrix& SquareMatrix::operator/=(float scalar) {
    // Division by scalar
    auto divide = [&] (int i, int j) {return this->getValue(i, j) / scalar;};
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
    auto transpose = [&] (int i, int j) {return this->getValue(j, i);};
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
                m(newRowIndex,newColumnIndex) = this->getValue(row, column);
            }
        }
    }
    return m;
}

float SquareMatrix::pureDeterminant() const {
    // Matrix determinant without using cofactor matrix
    if(dimensions() == 1) {
        return this->getValue(0,0);
    } else {
        float result = 0;
        for (int j = 0; j < dimensions(); ++j) {
            result += pow(-1,j+2) * subMatrix(0, j).pureDeterminant() * this->getValue(0,j);
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
        return this->getValue(0, 0);
    } else {
        // First compute the cofactor matrix
        computeCofactorMatrix();
        // Use the cofactor matrix to compute the determinant
        float result = 0;
        for (int j = 0; j < dimensions(); ++j) {
            result += (*cofactors)(j,0) * this->getValue(0, j);
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
    return width;
}

Vector SquareMatrix::column(int index) const {
    // Get a column as vector
    Vector v = Vector(dimensions());
    for (int row = 0; row < dimensions(); ++row) {
        v[row] = this->getValue(row, index);
    }
    return v;
}

Vector SquareMatrix::row(int index) const {
    // Get a row as vector
	Vector v = Vector(dimensions());
	for (int col = 0; col < dimensions(); ++col) {
		v[col] = this->getValue(index, col);
	}
	return v;
}

float& SquareMatrix::operator()(int row, int column) {
    // Element access
    cofactorsAreStale = true;
    return this->getValue(row, column); // calls non-const
}

float SquareMatrix::operator()(int row, int column) const {
    // Element access
    return this->getValue(row, column); // calls const
}