#include "Camera.h"

void Camera::init()
{
	x = 0, y = 0;
	width = 1024, height = 768;		// Set these to the desired size of the viewport
}

void Camera::update(int x, int y)
{
	this->x = x;
	this->y = y;

	if (this->y < 0)
	{
		this->y = 0;
	}
}

Camera::Camera()
{
}


Camera::~Camera()
{
}
