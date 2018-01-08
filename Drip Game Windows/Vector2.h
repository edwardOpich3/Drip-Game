#pragma once

// TODO: FIX THIS FOR THE LOVE OF GOD! This is SO hacky!!!
class Vector3;

class Vector2
{
private:

	float data[2];							// Stores the floats

public:

	float &x = data[0];						// x component of our vector
	float &y = data[1];						// y component of our vector

	float dot(Vector2 other);		// Returns the dot product of this vector with the other
	float magnitude();				// Returns the magnitude of our vector
	float sqrMagnitude();			// Returns the squared magnitude of our vector; is quicker
	void normalize();				// Normalizes the vector; makes its magnitude 1 while preserving direction


	float& operator[](int index);					// Edit a float in the vector
	const float& operator[](int index) const;		// Read a float from the vector
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
	Vector2(Vector3 a);

	Vector2(const Vector2& b);	// Copy Constructor
	~Vector2();
};