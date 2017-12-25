#include "Vector3.h"
#include <math.h>

float Vector3::dot(Vector3 other)
{
	return (data[0] * other.data[0]) + (data[1] * other.data[1]);
}

float Vector3::magnitude()
{
	return sqrtf(sqrMagnitude());
}

float Vector3::sqrMagnitude()
{
	float myFloat = 0.0f;

	for (unsigned int i = 0; i < 3; i++)
	{
		myFloat += powf(data[i], 2);
	}

	return myFloat;
}

void Vector3::normalize()
{
	for (unsigned int i = 0; i < 3; i++)
	{
		data[i] = data[i] / magnitude();
	}
}


float& Vector3::operator[](int index)
{
	return data[index];
}

const float& Vector3::operator[](int index) const
{
	return data[index];
}


Vector3& Vector3::operator=(const Vector3& other)
{
	if (&other != this)
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			data[i] = other.data[i];
		}
	}

	return *this;
}

Vector3 operator*(Vector3 a, const float& b)
{
	a *= b;
	return a;
}

Vector3& Vector3::operator*=(float b)
{
	for (unsigned int i = 0; i < 3; i++)
	{
		data[i] *= b;
	}

	return *this;
}

Vector3 operator/(Vector3 a, const float& b)
{
	a /= b;
	return a;
}

Vector3& Vector3::operator/=(float b)
{
	for (unsigned int i = 0; i < 3; i++)
	{
		data[i] /= b;
	}

	return *this;
}

Vector3 operator-(Vector3 a, const Vector3& b)
{
	a -= b;
	return a;
}

Vector3& Vector3::operator-=(Vector3 b)
{
	for (unsigned int i = 0; i < 3; i++)
	{
		data[i] -= b.data[i];
	}

	return *this;
}

Vector3::Vector3()
{
	data[0] = 0.0f;
	data[1] = 0.0f;
	data[2] = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
{
	data[0] = x;
	data[1] = y;
	data[2] = z;
}

Vector3::Vector3(const Vector3& b)
{
	*this = b;
}

Vector3::~Vector3()
{
}
