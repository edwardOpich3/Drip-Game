#pragma once
#include "GameObject.h"
#include "Camera.h"
class Formation
{
public:

	int x, y;	// Top-leftmost pixel of the formation
	int numObjects;			// Number of objects in the formation
	GameObject* objects = nullptr;	// Objects container

	void load(int x, int y, ALLEGRO_BITMAP** obstacleSpr, ALLEGRO_BITMAP** powerupSpr);		// Loads the formation with objects and places it at (x, y)
	void draw(Camera camera);																// Draws all objects in the formation
	void removeObject(int index);		// Removes an object from the formation
	void unload();						// Destroys the objects container

	Formation();
	~Formation();
};

