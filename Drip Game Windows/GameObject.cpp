#include "GameObject.h"

// TODO: Fix this! This code is so bad!
void GameObject::load(int type)
{
	this->type = type;
	x = 512.0f, y = 1024.0f;
	width = 256.0f, height = 256.0f;
	angle = 0.0f;
	size = 1.0f;
}

void GameObject::unload()
{

}

void GameObject::update()
{

}

void GameObject::draw(Camera camera)
{
	al_draw_scaled_rotated_bitmap(sprite, (al_get_bitmap_width(sprite) / 2.0f), (al_get_bitmap_height(sprite) / 2.0f), x - camera.x, y - camera.y, (size * width) / al_get_bitmap_width(sprite), (size * height) / al_get_bitmap_height(sprite), -angle * (ALLEGRO_PI / 180.0f), NULL);
}

// TODO: This function could use some working; ideally, rather than a point, it would check against another collision structure
bool GameObject::isColliding(float x, float y)
{
	// Obstacles may have unique collision
	if (!powerup)
	{
		switch (type)
		{
			// Clock
			case 0:
			{
				if (std::sqrtf(std::pow(x - this->x, 2) + std::pow(y - this->y, 2)) < (width / 2.0f))
				{
					return true;
				}
				return false;
			}
			default:
			{
				return false;
			}
		}
	}

	// All powerups have the same collision
	else
	{
		if (std::sqrtf(std::pow(x - this->x, 2) + std::pow(y - this->y, 2)) < (width / 2.0f))
		{
			return true;
		}
		return false;
	}
}

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}
