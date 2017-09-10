#pragma once
#include "allegro5/allegro.h"
#include "Camera.h"
#include <string>
class GameObject
{
public:

	float x, y;
	float width, height;
	float angle;
	float size;
	float type;

	int frame;
	int animationState;

	void load(float type);
	void unload();
	void draw(Camera camera, ALLEGRO_BITMAP* sprite);
	void update();

	GameObject();
	~GameObject();
};

