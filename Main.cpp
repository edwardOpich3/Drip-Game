#include "Game.h"

int main()
{
	// Set up the game, abort on failure
	if (!Game::initialize())
	{
		return -1;
	}

	// Main game loop
	while (!Game::quit)
	{
		// Handle input, timers, etc.
		Game::handleEvents();

		// It's time to update the frame!
		if (Game::update)
		{
			// Update the frame
			Game::updateFrame();
		}
	}

	// Unload assets from the current state
	Game::unload();

	// Free any memory and perform any other ending processes
	Game::end();
		
	return 0;
}