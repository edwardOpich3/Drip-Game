#pragma once
class Vector2
{

public:

	float x;						// x component of our vector
	float y;						// y component of our vector

	float dot(Vector2 other);		// Returns the dot product of this vector with the other
	float magnitude();				// Returns the magnitude of our vector
	float sqrMagnitude();			// Returns the squared magnitude of our vector; is quicker
	void normalize();				// Normalizes the vector; makes its magnitude 1 while preserving direction


	Vector2& operator=(const Vector2& other);

	// Arithmetic operators
	friend Vector2 operator*(Vector2 a, const float& b);
	Vector2& operator*=(float b);

	friend Vector2 operator/(Vector2 a, const float& b);
	Vector2& operator/=(float b);

	friend Vector2 operator-(Vector2 a, const Vector2& b);
	Vector2& operator-=(Vector2 b);

	Vector2();
	Vector2(float x, float y);
	~Vector2();
};