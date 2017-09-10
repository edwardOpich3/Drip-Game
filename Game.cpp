#include "Game.h"
#include "allegro5/allegro_image.h"
#include <string>
#include <sstream>

enum GAME_STATE { SPLASH, TITLE, GAME };
enum KEYS { LEFT, RIGHT };
enum OBSTACLES { CLOCK };
enum POWERUPS { FAST, SLOW, SIZE, TIME, LIFE };

ALLEGRO_DISPLAY* Game::display;
ALLEGRO_EVENT_QUEUE* Game::event;
ALLEGRO_TIMER* Game::timer;
ALLEGRO_BITMAP* Game::buffer;

bool Game::quit;
bool Game::update;
char Game::state;
bool Game::keys[] = { false, false };
int Game::level;

Player Game::player;
Camera Game::camera;
Shader Game::bgShader;

const int Game::numObstacles;
GameObject Game::obstacles[];

ALLEGRO_BITMAP* Game::background;
ALLEGRO_BITMAP* Game::bgBuffer;
ALLEGRO_BITMAP* Game::powerups[];

int Game::numObstacleSpr;
ALLEGRO_BITMAP** Game::obstacleSpr;

bool Game::initialize()
{
	// Initialize Allegro 5, check for success
	if (!al_init())
	{
		return false;
	}

	// Set any new window settings
	al_set_new_window_title("Drip Game");
	al_set_new_display_flags(ALLEGRO_PROGRAMMABLE_PIPELINE/* | ALLEGRO_OPENGL*/);	// Uncomment the " | ALLEGRO_OPENGL" to test using an OpenGL device

	// Initialize a window of size 1024 X 768, check for success
	display = al_create_display(1024, 768);

	if (!display)
	{
		return false;
	}

	// Initialize the event queue, check for success
	event = al_create_event_queue();

	if (!event)
	{
		return false;
	}

	// Install any inputs
	al_install_mouse();
	al_install_keyboard();

	// Register any event sources to be considered
	al_register_event_source(event, al_get_display_event_source(display));
	al_register_event_source(event, al_get_mouse_event_source());
	al_register_event_source(event, al_get_keyboard_event_source());

	// Set a timer to have the game's framerate set at 60, check for success
	timer = al_create_timer(1.0f / 60.0f);

	if (!timer)
	{
		return false;
	}

	// Register the timer as an event source
	al_register_event_source(event, al_get_timer_event_source(timer));

	// Initialize any addons
	al_init_image_addon();

	// Create the buffer bitmap
	buffer = al_create_bitmap(1024, 768);
	bgBuffer = al_create_bitmap(1024, 768);

	// Various game loop variables
	quit = false;
	update = false;
	state = GAME;
	level = 1;

	// Initialize for the first state
	load();

	// Begin the timer; should be last step before game loop
	al_start_timer(timer);

	return true;
}

void Game::handleEvents()
{
	// Create a new event holder and wait for an event
	ALLEGRO_EVENT e;
	al_wait_for_event(Game::event, &e);

	// Parse event type, react accordingly
	switch (e.type)
	{
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
		{
			quit = true;
			break;
		}

		case ALLEGRO_EVENT_KEY_DOWN:
		{
			if (e.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				quit = true;
			}
			if (e.keyboard.keycode == ALLEGRO_KEY_LEFT)
			{
				keys[LEFT] = true;
			}
			if (e.keyboard.keycode == ALLEGRO_KEY_RIGHT)
			{
				keys[RIGHT] = true;
			}
			break;
		}

		case ALLEGRO_EVENT_KEY_UP:
		{
			if (e.keyboard.keycode == ALLEGRO_KEY_LEFT)
			{
				keys[LEFT] = false;
			}
			if (e.keyboard.keycode == ALLEGRO_KEY_RIGHT)
			{
				keys[RIGHT] = false;
			}
		}

		case ALLEGRO_EVENT_TIMER:
		{
			// Check if the timer in question is in fact the update timer
			if (e.timer.source == Game::timer)
			{
				update = true;
			}
			break;
		}
	}
}

void Game::updateFrame()
{
	// Ensure the frame isn't updated again before next frame
	update = false;

	// Do any drawing to the buffer
	al_set_target_bitmap(Game::buffer);
	al_clear_to_color(al_map_rgb(128, 128, 128));

	switch (state)
	{
		case SPLASH:
		{
			break;
		}

		case TITLE:
		{
			break;
		}

		case GAME:
		{
			al_use_shader(bgShader.shader);

			float texSize[2] = { (float)al_get_bitmap_width(background), (float)al_get_bitmap_height(background) };
			al_set_shader_float_vector("texSize", 2, texSize, 1);

			al_set_shader_sampler("bg_tex", background, 1);

			float bufferSize[2] = { 1024, 768 };
			al_set_shader_float_vector("bufferSize", 2, bufferSize, 1);

			float cameraPos[2] = { (float)camera.x, (float)camera.y };
			al_set_shader_float_vector("cameraPos", 2, cameraPos, 1);

			al_draw_bitmap(bgBuffer, 0, 0, NULL);

			al_use_shader(NULL);

			obstacles[0].draw(camera, obstacleSpr[0]);

			camera.update(player.x - 512, player.y - 64);
			player.update(keys, camera);
			break;
		}
	}

	// Draw the final buffer to the screen
	al_set_target_backbuffer(Game::display);
	al_draw_bitmap(Game::buffer, 0, 0, NULL);
	al_flip_display();
}

void Game::load()
{
	switch (state)
	{
		case SPLASH:
		{
			break;
		}
		case TITLE:
		{
			break;
		}
		case GAME:
		{
			loadBG();
			loadPowerups();
			loadObstacles();
			camera.init();
			player.init();
			bgShader.load(display, "shaders/Vertex Shader", "shaders/BG Pixel Shader");

			obstacles[0].load(CLOCK);

			break;
		}
	}
}

void Game::loadBG()
{
	std::string path = "data/bgs/bg";
	std::stringstream convert;
	convert << level;
	path += convert.str();
	path += ".png";
	background = al_load_bitmap(path.c_str());
}

void Game::loadPowerups()
{
	std::stringstream convert;
	std::string path;
	for (int i = 0; i < 5; i++)
	{
		path = "data/sprites/powerups/";
		convert << i;
		path += convert.str();
		path += ".png";
		powerups[i] = al_load_bitmap(path.c_str());
	}
}

void Game::loadObstacles()
{
	std::stringstream convert;
	std::string path;

	switch (level)
	{
		case 1:
		{
			numObstacleSpr = 1;
			obstacleSpr = new ALLEGRO_BITMAP*[numObstacleSpr];
			for (int i = 0; i < numObstacleSpr; i++)
			{
				path = "data/sprites/obstacles/";
				convert << i;
				path += convert.str();
				path += ".png";
				obstacleSpr[i] = al_load_bitmap(path.c_str());
			}
			break;
		}
	}
}

void Game::unloadPowerups()
{
	for (int i = 0; i < 5; i++)
	{
		al_destroy_bitmap(powerups[i]);
	}
}

void Game::unloadObstacles()
{
	for (int i = 0; i < numObstacleSpr; i++)
	{
		al_destroy_bitmap(obstacleSpr[i]);
	}
	delete obstacleSpr;
}

void Game::unload()
{
	switch (state)
	{
		case SPLASH:
		{
			break;
		}
		case TITLE:
		{
			break;
		}
		case GAME:
		{
			al_destroy_bitmap(background);
			unloadPowerups();
			unloadObstacles();
			player.unload();
			bgShader.unload();

			obstacles[0].unload();

			break;
		}
	}
}

void Game::end()
{
	// Free any memory that needs to be freed
	al_destroy_bitmap(buffer);
	al_destroy_bitmap(bgBuffer);
	al_destroy_timer(timer);
	al_destroy_event_queue(event);
	al_destroy_display(display);
}