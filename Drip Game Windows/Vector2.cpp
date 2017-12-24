#include "Vector2.h"
#include <math.h>

float Vector2::dot(Vector2 other)
{
	return (data[0] * other.data[0]) + (data[1] * other.data[1]);
}

float Vector2::magnitude()
{
	return sqrtf(sqrMagnitude());
}

float Vector2::sqrMagnitude()
{
	float myFloat = 0.0f;

	for (unsigned int i = 0; i < 2; i++)
	{
		myFloat += powf(data[i], 2);
	}

	return myFloat;
}

void Vector2::normalize()
{
	for (unsigned int i = 0; i < 2; i++)
	{
		data[i] = data[i] / magnitude();
	}
}


float& Vector2::operator[](int index)
{
	return data[index];
}

const float& Vector2::operator[](int index) const
{
	return data[index];
}


Vector2& Vector2::operator=(const Vector2& other)
{
	if (&other != this)
	{
		for (unsigned int i = 0; i < 2; i++)
		{
			data[i] = other.data[i];
		}
	}

	return *this;
}

Vector2 operator*(Vector2 a, const float& b)
{
	a *= b;
	return a;
}

Vector2& Vector2::operator*=(float b)
{
	for (unsigned int i = 0; i < 2; i++)
	{
		data[i] *= b;
	}

	return *this;
}

Vector2 operator/(Vector2 a, const float& b)
{
	a /= b;
	return a;
}

Vector2& Vector2::operator/=(float b)
{
	for (unsigned int i = 0; i < 2; i++)
	{
		data[i] /= b;
	}

	return *this;
}

Vector2 operator-(Vector2 a, const Vector2& b)
{
	a -= b;
	return a;
}

Vector2& Vector2::operator-=(Vector2 b)
{
	for (unsigned int i = 0; i < 2; i++)
	{
		data[i] -= b.data[i];
	}

	return *this;
}

Vector2::Vector2()
{
	data[0] = 0.0f;
	data[1] = 0.0f;
}

Vector2::Vector2(float x, float y)
{
	data[0] = x;
	data[1] = y;
}

Vector2::Vector2(const Vector2& b)
{
	*this = b;
}

Vector2::~Vector2()
{
}
