#pragma once
#include "Vector2.h"

class Matrix3
{
private:

	Vector2 data[3];

public:

	Vector2& operator[](int index);		// Edit a vector in the matrix
	const Vector2& operator[](int index) const;		// Read a vector from the matrix
	Matrix3& operator=(const Matrix3& b);		// Copy Assignment Operator

	friend Vector2 operator*(Matrix3 a, const Vector2& b);		// Multiplication with a vector on the right

	friend Matrix3 operator*(Matrix3 a, const Matrix3& b);		// Multiplication with another matrix on the right
	Matrix3& operator*=(const Matrix3& b);

	Matrix3();
	Matrix3(const Matrix3& b);	// Copy Constructor

	~Matrix3();
};

