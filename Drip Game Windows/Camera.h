#pragma once
class Camera
{
public:

	int x, y;				// Top-left corner of the camera's viewport in the world, in pixels
	int width, height;		// Width and height of the camera, in pixels

	void init();				// Sets values to defaults
	void update(int x, int y);	// Updates x and y according to parameters

	Camera();
	~Camera();
};

