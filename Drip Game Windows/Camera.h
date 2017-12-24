#pragma once
#include "Vector2.h"

class Camera
{
public:

	Vector2 position;		// Top-left corner of the camera's viewport in the world, in pixels
	Vector2 size;			// Width and height of the camera, in pixels

	void init();					// Sets values to defaults
	void update(Vector2 position);	// Updates x and y according to parameters

	Camera& operator=(const Camera& other);

	Camera();
	Camera(const Camera& other);
	~Camera();
};

