#pragma once
#include "allegro5/allegro.h"
#include "Camera.h"
#include <string>
class GameObject
{
public:

	Vector2 position;		// Position of the center of the object
	Vector2 size;			// Width and height of the object, in pixels
	float angle;			// Angle the object is tilted at (0.0f being its normal angle, increasing counter-clockwise)
	float scale;			// Size of the object (1 = width of 128 pixels)
	int type;				// Type index of object
	int powerup;			// Is the object a powerup, obstacle, or invalid type?

	// Pointer to the object's sprite
	ALLEGRO_BITMAP* sprite;

	int frame;				// Current frame, for animated objects
	int animationState;		// Current animation state, for animated objects

	void draw(Camera camera);				// Draws the object
	bool isColliding(Vector2 position);		// Does this object intersect with the given position?

	GameObject& operator=(const GameObject& other);

	GameObject();
	GameObject(const GameObject& other);
	~GameObject();
};

