#pragma once
#include "allegro5\allegro.h"
class Input
{
public:

	enum KEYS { LEFT, RIGHT, UP, DOWN };					// Keycodes for the keyboard

	static const unsigned int numKeys = 4;					// How many keys do we need to keep track of?
	static bool keys[numKeys];								// State of the keys

	static void handleEvents(ALLEGRO_EVENT e);				// Handles all input events we care about

	Input();
	~Input();
};

