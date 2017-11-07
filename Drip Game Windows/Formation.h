#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Container.h"
class Formation
{
public:

	int x, y;	// Top-leftmost pixel of the formation
	Container<GameObject> objects;	// Objects container
	static int numFiles;	// Number of formation files in the current level's formation directory

	void load(int x, int y, Container<ALLEGRO_BITMAP*> obstacleSpr, Container<ALLEGRO_BITMAP*> powerupSpr);		// Loads the formation with objects and places it at (x, y)
	void draw(Camera camera);																// Draws all objects in the formation
	void unload();		// Destroys the objects container
	void getNumFiles();	// Gets the number of formation files in the current level's formation directory

	static void eraseNumFiles();	// Sets the number of files to 0. For unloading the scene.

	Formation operator=(const Formation& other);

	Formation();
	Formation(const Formation& other);
	~Formation();
};

