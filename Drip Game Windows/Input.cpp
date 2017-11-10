#include "Input.h"

bool Input::keys[];

void Input::handleEvents(ALLEGRO_EVENT e)
{
	if (e.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		if (e.keyboard.keycode == ALLEGRO_KEY_LEFT)
		{
			keys[LEFT] = true;
		}
		if (e.keyboard.keycode == ALLEGRO_KEY_RIGHT)
		{
			keys[RIGHT] = true;
		}
		if (e.keyboard.keycode == ALLEGRO_KEY_UP)
		{
			keys[UP] = true;
		}
		if (e.keyboard.keycode == ALLEGRO_KEY_DOWN)
		{
			keys[DOWN] = true;
		}
		if (e.keyboard.keycode == ALLEGRO_KEY_ENTER)
		{
			keys[ENTER] = true;
		}
	}

	else if (e.type == ALLEGRO_EVENT_KEY_UP)
	{
		if (e.keyboard.keycode == ALLEGRO_KEY_LEFT)
		{
			keys[LEFT] = false;
		}
		if (e.keyboard.keycode == ALLEGRO_KEY_RIGHT)
		{
			keys[RIGHT] = false;
		}
		if (e.keyboard.keycode == ALLEGRO_KEY_UP)
		{
			keys[UP] = false;
		}
		if (e.keyboard.keycode == ALLEGRO_KEY_DOWN)
		{
			keys[DOWN] = false;
		}
		if (e.keyboard.keycode == ALLEGRO_KEY_ENTER)
		{
			keys[ENTER] = false;
		}
	}
}

Input::Input()
{
	for (unsigned int i = 0; i < numKeys; i++)
	{
		keys[i] = false;
	}
}


Input::~Input()
{
}
