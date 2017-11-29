#include "Vector2.h"
#include <math.h>

float Vector2::dot(Vector2 other)
{
	return (x * other.x) + (y * other.y);
}

float Vector2::magnitude()
{
	return sqrtf(sqrMagnitude());
}

float Vector2::sqrMagnitude()
{
	return powf(x, 2) + powf(y, 2);
}

void Vector2::normalize()
{
	x = x / magnitude();
	y = y / magnitude();
}



Vector2& Vector2::operator=(const Vector2& other)
{
	if (&other != this)
	{
		x = other.x;
		y = other.y;
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
	x *= b;
	y *= b;
	return *this;
}

Vector2 operator/(Vector2 a, const float& b)
{
	a /= b;
	return a;
}

Vector2& Vector2::operator/=(float b)
{
	x /= b;
	y /= b;
	return *this;
}

Vector2 operator-(Vector2 a, const Vector2& b)
{
	a -= b;
	return a;
}

Vector2& Vector2::operator-=(Vector2 b)
{
	x -= b.x;
	y -= b.y;
	return *this;
}

Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}


Vector2::~Vector2()
{
}
