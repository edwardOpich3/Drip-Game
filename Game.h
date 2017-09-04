#pragma once
#include "allegro5/allegro.h"
#include "Player.h"
#include "Camera.h"
#include "Shader.h"
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

	static Player player;
	static Camera camera;
	static Shader shader;

	static ALLEGRO_BITMAP* background;
	static ALLEGRO_BITMAP* bgBuffer;

	static bool initialize();
	static void handleEvents();
	static void updateFrame();
	static void load();
	static void unload();
	static void end();
};

