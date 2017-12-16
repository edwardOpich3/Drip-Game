#include "Matrix2.h"

Vector2& Matrix2::operator[](int index)
{
	return data[index];
}

const Vector2& Matrix2::operator[](int index) const
{
	return data[index];
}

Matrix2& Matrix2::operator=(const Matrix2& b)
{
	for (unsigned int i = 0; i < 2; i++)
	{
		data[i] = b.data[i];
	}

	return *this;
}

// Identity M2
Matrix2::Matrix2()
{
	data[0] = Vector2(1.0f, 0.0f);
	data[1] = Vector2(0.0f, 1.0f);
}

Matrix2::Matrix2(const Matrix2& b)
{
	*this = b;
}

Matrix2::~Matrix2()
{
}
