#pragma once
#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "Player.h"
#include "Camera.h"
#include "Shader.h"
#include "Formation.h"
#include "Cursor.h"
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
	static char phase;		// What phase are we in in our current state?
	static int level;		// Current level; determines the wall, obstacles, and formations

	// Game related objects
	static Player player;
	static Camera camera;
	static Shader bgShader;	// Infinite scrolling BG shader
	static Cursor cursor;

	// Formations
	static Container<Formation> formations;	// Container of object formations

	// Various bitmaps
	static ALLEGRO_BITMAP* background;	// The background graphic to draw
	static ALLEGRO_BITMAP* bgBuffer;	// The buffer to draw to the screen in lieu of the background graphic

	static ALLEGRO_BITMAP* uiBitmap;	// The current ui graphic. TODO: Is this a good way to do this? Fix it if not!
	static ALLEGRO_BITMAP* splashBitmap;	// The bitmap for the splash screen
	static ALLEGRO_BITMAP* titleBitmap;	// The bitmap for the logo.

	static Container<ALLEGRO_BITMAP*> powerups;	// The powerup bitmaps
	static Container<ALLEGRO_BITMAP*> obstacleSpr;	// Container of obstacle bitmaps

	// Fonts
	static Container<ALLEGRO_FONT*> hudFont;	// The fonts used for the HUD; size 26, size 34, size 22 bold

	// Core engine functions
	static bool initialize();
	static void handleEvents();
	static void updateFrame();

	// Loading
	static void load();	// Loads everything
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

