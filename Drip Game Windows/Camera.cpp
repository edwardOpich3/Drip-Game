#include "Camera.h"

void Camera::init()
{
	position = Vector2(0.0f, 0.0f);
	size = Vector2(1024.0f, 768.0f);		// Set these to the desired size of the viewport
}

void Camera::update(Vector2 position)
{
	this->position = position;

	if (this->position.y < 0)
	{
		this->position.y = 0;
	}
}

Camera& Camera::operator=(const Camera& other)
{
	if (this != &other)
	{
		position = other.position;
		size = other.size;
	}

	return *this;
}

Camera::Camera()
{
}

Camera::Camera(const Camera& other)
{
	*this = other;
}

Camera::~Camera()
{
}
