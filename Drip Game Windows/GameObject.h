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
	int type;
	int powerup;

	ALLEGRO_BITMAP* sprite;

	int frame;
	int animationState;

	void load(int type);
	void unload();
	void draw(Camera camera);
	void update();

	GameObject();
	~GameObject();
};

