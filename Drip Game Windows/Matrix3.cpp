#include "Matrix3.h"

Vector2& Matrix3::operator[](int index)
{
	return data[index];
}

const Vector2& Matrix3::operator[](int index) const
{
	return data[index];
}

Matrix3& Matrix3::operator=(const Matrix3& b)
{
	if (&b != this)
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			data[i] = b.data[i];
		}
	}

	return *this;
}

Vector2 operator*(Matrix3 a, const Vector2& b)
{
	Vector2 myVector;

	for (unsigned int i = 0; i < 3; i++)
	{
		for (unsigned int j = 0; j < 3; j++)
		{
			myVector[j] += a[i][j] * b[j];
		}
	}

	return myVector;
}

Matrix3 operator*(Matrix3 a, const Matrix3& b)
{
	a *= b;
	return a;
}

Matrix3& Matrix3::operator*=(const Matrix3& b)
{
	Matrix3 myMatrix;

	// Pick a row in our matrix
	for (unsigned int i = 0; i < 3; i++)
	{
		// Pick a column in our matrix
		for (unsigned int j = 0; j < 3; j++)
		{
			// Iterates through columns/rows in this/b
			for (unsigned int k = 0; k < 3; k++)
			{
				myMatrix[i][j] += data[i][k] * b[k][j];
			}
		}
	}

	*this = myMatrix;
	return *this;
}

// Identity M3
Matrix3::Matrix3()
{
	data[0] = Vector2(1.0f, 0.0f);
	data[1] = Vector2(0.0f, 1.0f);
}

Matrix3::Matrix3(const Matrix3& b)
{
	*this = b;
}

Matrix3::~Matrix3()
{
}
