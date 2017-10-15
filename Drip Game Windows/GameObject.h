#pragma once
#include "allegro5/allegro.h"
#include "Camera.h"
#include <string>
class GameObject
{
public:

	float x, y;				// Position of the center of the object
	float width, height;	// Width and height of the object, in pixels
	float angle;			// Angle the object is tilted at (0.0f being its normal angle, increasing counter-clockwise)
	float size;				// Size of the object (1 = width of 128 pixels)
	int type;				// Type index of object
	int powerup;			// Is the object a powerup, obstacle, or invalid type?

	// Pointer to the object's sprite
	ALLEGRO_BITMAP* sprite;

	int frame;				// Current frame, for animated objects
	int animationState;		// Current animation state, for animated objects

	void load(int type);	// Loads the object based on type
	void unload();				// Unloads the object
	void draw(Camera camera);	// Draws the object
	void update();				// Updates the object
	bool isColliding(float x, float y);		// Does this object intersect with the given position?

	GameObject();
	~GameObject();
};

