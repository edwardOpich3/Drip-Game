#pragma once
#include "allegro5\allegro.h"
class Cursor
{
public:

	int x, y;					// Current position of cursor
	int selection;				// Current selection; used for when the user picks something
	int maxSelection;			// Maximum selection possible

	bool isVertical;			// Should the cursor move vertically, or horizontally?
	unsigned int distance;		// Distance between items

	ALLEGRO_BITMAP* image;		// Image used as the cursor

	int update();				// Updates the cursor based on input; if a selection was made, its value is returned
	void draw();				// Draws the cursor to the correct location on screen.

	Cursor();
	Cursor(ALLEGRO_BITMAP* image, int x, int y, unsigned int distance, bool isVertical, int maxSelection);
	~Cursor();
};

