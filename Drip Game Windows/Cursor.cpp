#include "Cursor.h"
#include "Input.h"

Cursor::Cursor()
{
}

Cursor::Cursor(ALLEGRO_BITMAP* image, Vector2 position, unsigned int distance, bool isVertical, int maxSelection)
{
	this->image = image;
	this->position = position;
	this->distance = distance;
	this->isVertical = isVertical;
	this->maxSelection = maxSelection;

	selection = 0;

	// Make sure the user doesn't accidentially make a choice or move the cursor, should they be holding any keys
	for (unsigned int i = 0; i < Input::numKeys; i++)
	{
		Input::keys[i] = false;
	}
}

Cursor::Cursor(const Cursor& b)
{
	*this = b;
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
		al_draw_bitmap(image, position.x, position.y + (selection * distance), NULL);
	}
}

Cursor& Cursor::operator=(const Cursor& other)
{
	if (this != &other)
	{
		image = other.image;
		position = other.position;
		distance = other.distance;
		isVertical = other.isVertical;
		maxSelection = other.maxSelection;
		selection = other.selection;
	}

	return *this;
}