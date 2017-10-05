#include "GameObject.h"

// Super-duper hacky, fix this later!
void GameObject::load(int type)
{
	this->type = type;
	x = 512.0f, y = 1024.0f;
	width = 256.0f, height = 256.0f;
	angle = 270.0f;
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
	al_draw_scaled_rotated_bitmap(sprite, (al_get_bitmap_width(sprite) / 2.0f), (al_get_bitmap_height(sprite) / 2.0f), x - camera.x, y - camera.y, size * (width / al_get_bitmap_width(sprite)), size * (height / al_get_bitmap_height(sprite)), -angle * (ALLEGRO_PI / 180.0f), NULL);
}

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}
