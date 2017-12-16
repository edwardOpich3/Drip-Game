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

Vector2 operator*(Matrix2 a, const Vector2& b)
{
	Vector2 myVector;

	for (unsigned int i = 0; i < 2; i++)
	{
		for (unsigned int j = 0; j < 2; j++)
		{
			myVector[j] += a[i][j] * b[j];
		}
	}

	return myVector;
}

Matrix2 operator*(Matrix2 a, const Matrix2& b)
{
	a *= b;
	return a;
}

Matrix2& Matrix2::operator*=(const Matrix2& b)
{
	Matrix2 myMatrix;

	// Pick a row in our matrix
	for (unsigned int i = 0; i < 2; i++)
	{
		// Pick a column in our matrix
		for (unsigned int j = 0; j < 2; j++)
		{
			// Iterates through columns/rows in this/b
			for (unsigned int k = 0; k < 2; k++)
			{
				myMatrix[i][j] += data[i][k] * b[k][j];
			}
		}
	}

	return myMatrix;
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
