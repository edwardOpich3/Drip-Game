#include "Cursor.h"
#include "Input.h"

Cursor::Cursor()
{
}

Cursor::Cursor(ALLEGRO_BITMAP* image, int x, int y, unsigned int distance, bool isVertical, int maxSelection)
{
	this->image = image;
	this->x = x;
	this->y = y;
	this->distance = distance;
	this->isVertical = isVertical;
	this->maxSelection = maxSelection;

	selection = 0;
}

Cursor::~Cursor()
{
}

int Cursor::update()
{
	if (isVertical)
	{
		if (Input::keys[Input::UP])
		{
			selection--;

			if (selection < 0)
			{
				selection = maxSelection;
			}

			Input::keys[Input::UP] = false;
		}
		else if (Input::keys[Input::DOWN])
		{
			selection++;
			
			if (selection > maxSelection)
			{
				selection = 0;
			}

			Input::keys[Input::DOWN] = false;
		}
	}

	if (Input::keys[Input::ENTER])
	{
		return selection;
	}
	else
	{
		return -1;
	}
}

void Cursor::draw()
{
	if (isVertical)
	{
		al_draw_bitmap(image, x, y + (selection * distance), NULL);
	}
}