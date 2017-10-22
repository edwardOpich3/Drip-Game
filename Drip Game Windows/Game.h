#pragma once
#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "Player.h"
#include "Camera.h"
#include "Shader.h"
#include "Formation.h"
class Game
{
public:

	// TODO: Consider putting all loading and unloading functions except for load and unload in an IO class!

	// Necessary objects for the allegro program to run
	static ALLEGRO_DISPLAY* display;
	static ALLEGRO_EVENT_QUEUE* event;
	static ALLEGRO_TIMER* timer;			// Determines the frame rate
	static ALLEGRO_BITMAP* buffer;			// Draw to this before drawing to the screen

	static bool quit;		// Has the program received a quit command?
	static bool update;		// Is it time to update the screen?
	static char state;		// What's the current game state?
	static bool keys[2];	// Array to hold the current keyboard state (to later be moved to its own class)
	static int level;		// Current level; determines the wall, obstacles, and formations

	// Game related objects
	static Player player;
	static Camera camera;
	static Shader bgShader;	// Infinite scrolling BG shader

	// Formations
	static Container<Formation> formations;	// Container of object formations

	// Various bitmaps
	static ALLEGRO_BITMAP* background;	// The background graphic to draw
	static ALLEGRO_BITMAP* bgBuffer;	// The buffer to draw to the screen in lieu of the background graphic
	static ALLEGRO_BITMAP* powerups[5];	// The powerup bitmaps

	// Fonts
	static ALLEGRO_FONT* hudFont[3];	// The fonts used for the HUD; size 26, size 34, size 22 bold

	// Obstacle Sprites (TODO: Put this all in a container class!)
	static int numObstacleSpr;			// Number of obstacle sprites loaded
	static ALLEGRO_BITMAP** obstacleSpr;// Container of obstacle bitmaps

	// Core engine functions
	static bool initialize();
	static void handleEvents();
	static void updateFrame();

	// Loading
	static void load();	// Loads everything for gameplay (TODO: Name change, or set it up to load different states)
	static void loadGraphics();			// Loads all graphics
	static void loadBG();				// Loads the background graphic
	static void loadPowerupData();		// Loads powerup sprites
	static void loadObstacleData();		// Loads obstacle sprites

	// Unloading
	static void unload();				// Unloads everything
	static void unloadGraphics();		// Unloads all graphics
	static void unloadPowerupData();	// Destroys powerup sprites
	static void unloadObstacleData();	// Destroys obstacle sprites

	// End of Program
	static void end();	// Runs final shutdown procedures
};

