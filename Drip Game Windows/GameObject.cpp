#include "GameObject.h"

void GameObject::draw(Camera camera)
{
	al_draw_scaled_rotated_bitmap(sprite, (al_get_bitmap_width(sprite) / 2.0f), (al_get_bitmap_height(sprite) / 2.0f), position.x - camera.position.x, position.y - camera.position.y, size.x / al_get_bitmap_width(sprite), size.y / al_get_bitmap_height(sprite), -angle * (ALLEGRO_PI / 180.0f), NULL);
}

// TODO: This function could use some working; ideally, rather than a point, it would check against another collision structure
bool GameObject::isColliding(Vector2 position)
{
	// Obstacles may have unique collision
	if (!powerup)
	{
		switch (type)
		{
			// Clock
			case 0:
			{
				if (std::sqrtf(std::pow(position.x - this->position.x, 2) + std::pow(position.y - this->position.y, 2)) < (size.x / 2.0f))
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
		if (std::sqrtf(std::pow(position.x - this->position.x, 2) + std::pow(position.y - this->position.y, 2)) < (size.x / 2.0f))
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
