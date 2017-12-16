#pragma once
#include "Vector2.h"

class Matrix2
{
private:

	Vector2 data[2];	// Fixed-size array because there will always be only 2 vectors

public:

	Vector2& operator[](int index);		// Edit a vector in the matrix
	const Vector2& operator[](int index) const;		// Read a vector from the matrix
	Matrix2& operator=(const Matrix2& b);		// Copy Assignment Operator

	// TODO: Implement multiplication functions with Vector2 class!

	Matrix2();
	Matrix2(const Matrix2& b);	// Copy Constructor

	~Matrix2();
};

