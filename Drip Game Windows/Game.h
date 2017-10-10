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

	static int numFormations;
	static int formationsSize;
	static Formation* formations;

	static ALLEGRO_BITMAP* background;
	static ALLEGRO_BITMAP* bgBuffer;
	static ALLEGRO_BITMAP* powerups[5];

	static ALLEGRO_FONT* hudFont[3];

	static int numObstacleSpr;
	static ALLEGRO_BITMAP** obstacleSpr;

	static bool initialize();
	static void handleEvents();
	static void updateFrame();

	static void resizeFormations();
	static void removeFormation(int index);

	static void load();
	static void loadBG();
	static void loadPowerupData();
	static void loadObstacleData();

	static void unloadPowerupData();
	static void unloadObstacleData();
	static void unload();

	static void end();
};

