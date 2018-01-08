#pragma once
#include "Vector2.h"
#include "Matrix3.h"
class Collision
{

	float radius;				// Radius of the collision circle

	bool usesOBB;				// Does this object use an OBB, or the circle?

	Vector2 center;				// Global center of the OBB
	Vector2 min;				// Global minimum of the OBB
	Vector2 max;				// Global maximum of the OBB

	Vector2 orientation;		// Orientation of the OBB
	Matrix3 objectToWorld;		// Object to World Rotation Matrix

public:
	
	bool isColliding(Collision other);		// Is this rigidbody colliding with the other?

	Vector2 getHalfWidth();

	Collision& operator=(const Collision& other);

	Collision();
	Collision(const Collision& other);
	~Collision();

};

