#pragma once
#include "Vector3.h"

class Matrix3
{
private:

	Vector3 data[3];

public:

	Vector3& operator[](int index);		// Edit a vector in the matrix
	const Vector3& operator[](int index) const;		// Read a vector from the matrix
	Matrix3& operator=(const Matrix3& b);		// Copy Assignment Operator

	friend Vector3 operator*(Matrix3 a, const Vector3& b);		// Multiplication with a vector on the right

	friend Matrix3 operator*(Matrix3 a, const Matrix3& b);		// Multiplication with another matrix on the right
	Matrix3& operator*=(const Matrix3& b);

	Matrix3();
	Matrix3(const Matrix3& b);	// Copy Constructor

	~Matrix3();
};

