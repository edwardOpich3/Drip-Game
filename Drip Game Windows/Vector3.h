#pragma once
class Vector3
{
private:

	float data[3];							// Stores the floats

public:

	float &x = data[0];						// x component of our vector
	float &y = data[1];						// y component of our vector
	float &z = data[2];

	float dot(Vector3 other);		// Returns the dot product of this vector with the other
	float magnitude();				// Returns the magnitude of our vector
	float sqrMagnitude();			// Returns the squared magnitude of our vector; is quicker
	void normalize();				// Normalizes the vector; makes its magnitude 1 while preserving direction


	float& operator[](int index);					// Edit a float in the vector
	const float& operator[](int index) const;		// Read a float from the vector
	Vector3& operator=(const Vector3& other);

	// Arithmetic operators
	friend Vector3 operator*(Vector3 a, const float& b);
	Vector3& operator*=(float b);

	friend Vector3 operator/(Vector3 a, const float& b);
	Vector3& operator/=(float b);

	friend Vector3 operator-(Vector3 a, const Vector3& b);
	Vector3& operator-=(Vector3 b);

	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3& b);	// Copy Constructor
	~Vector3();
};