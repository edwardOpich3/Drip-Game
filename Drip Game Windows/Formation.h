#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Container.h"
class Formation
{
public:

	int x, y;	// Top-leftmost pixel of the formation
	Container<GameObject> objects;	// Objects container

	void load(int x, int y, Container<ALLEGRO_BITMAP*> obstacleSpr, Container<ALLEGRO_BITMAP*> powerupSpr);		// Loads the formation with objects and places it at (x, y)
	void draw(Camera camera);																// Draws all objects in the formation
	void unload();		// Destroys the objects container

	Formation operator=(const Formation& other);

	Formation();
	Formation(const Formation& other);
	~Formation();
};

