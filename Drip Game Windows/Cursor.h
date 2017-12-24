#pragma once
#include "allegro5\allegro.h"
#include "Vector2.h"
class Cursor
{
public:

	Vector2 position;			// Current position of cursor
	int selection;				// Current selection; used for when the user picks something
	int maxSelection;			// Maximum selection possible

	bool isVertical;			// Should the cursor move vertically, or horizontally?
	unsigned int distance;		// Distance between items

	ALLEGRO_BITMAP* image;		// Image used as the cursor

	int update();				// Updates the cursor based on input; if a selection was made, its value is returned
	void draw();				// Draws the cursor to the correct location on screen.

	Cursor& operator=(const Cursor& other);

	Cursor();
	Cursor(const Cursor& b);
	Cursor(ALLEGRO_BITMAP* image, Vector2 position, unsigned int distance, bool isVertical, int maxSelection);
	~Cursor();
};

