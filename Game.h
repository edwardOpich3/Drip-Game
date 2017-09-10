#pragma once
#include "allegro5/allegro.h"
#include "Player.h"
#include "Camera.h"
#include "Shader.h"
#include "GameObject.h"
class Game
{
public:

	static ALLEGRO_DISPLAY* display;
	static ALLEGRO_EVENT_QUEUE* event;
	static ALLEGRO_TIMER* timer;
	static ALLEGRO_BITMAP* buffer;

	static bool quit;
	static bool update;
	static char state;
	static bool keys[2];
	static int level;

	static Player player;
	static Camera camera;
	static Shader bgShader;

	const static int numObstacles = 5;
	static GameObject obstacles[numObstacles];

	static ALLEGRO_BITMAP* background;
	static ALLEGRO_BITMAP* bgBuffer;
	static ALLEGRO_BITMAP* powerups[5];

	static int numObstacleSpr;
	static ALLEGRO_BITMAP** obstacleSpr;

	static bool initialize();
	static void handleEvents();
	static void updateFrame();
	static void load();
	static void loadBG();
	static void loadPowerups();
	static void loadObstacles();
	static void unloadPowerups();
	static void unloadObstacles();
	static void unload();
	static void end();
};

