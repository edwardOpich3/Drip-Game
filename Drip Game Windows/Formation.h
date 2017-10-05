#pragma once
#include "GameObject.h"
#include "Camera.h"
class Formation
{
public:

	int x, y;	// Top-left
	int numObjects;			// Number of objects in the formation
	GameObject* objects = nullptr;	// Objects container

	void load(int x, int y, ALLEGRO_BITMAP** obstacleSpr);
	void draw(Camera camera);
	void unload();

	Formation();
	~Formation();
};

