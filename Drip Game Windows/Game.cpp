#include "Game.h"
#include "Container.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_ttf.h"
#include <string>
#include <sstream>
#include <fstream>
#include <random>
#include <ctime>

// Enums (TODO: Move certain enums to appropriate classes, if possible)
enum GAME_STATE { SPLASH, TITLE, GAME };	// Current game state
enum KEYS { LEFT, RIGHT, UP, DOWN };					// Keycodes for the keyboard

ALLEGRO_DISPLAY* Game::display;
ALLEGRO_EVENT_QUEUE* Game::event;
ALLEGRO_TIMER* Game::timer;
ALLEGRO_BITMAP* Game::buffer;

bool Game::quit;
bool Game::update;
char Game::state;
bool Game::keys[] = { false, false, false, false };
int Game::level;

Player Game::player;
Camera Game::camera;
Shader Game::bgShader;

Container<Formation> Game::formations;

ALLEGRO_BITMAP* Game::background;
ALLEGRO_BITMAP* Game::bgBuffer;
Container<ALLEGRO_BITMAP*> Game::powerups;

Container<ALLEGRO_FONT*> Game::hudFont;

Container<ALLEGRO_BITMAP*> Game::obstacleSpr;

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
	al_init_font_addon();
	al_init_ttf_addon();

	// Create the buffer bitmaps
	buffer = al_create_bitmap(1024, 768);
	bgBuffer = al_create_bitmap(1024, 768);

	// Initialize various game loop variables
	quit = false;
	update = false;
	state = GAME;
	level = 1;

	// Initialize for the first state
	load();

	// Seed the RNG!
	srand(time(0));

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
		// If the close button was pressed
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
		{
			quit = true;
			break;
		}

		// Check keys pressed this frame
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
			if (e.keyboard.keycode == ALLEGRO_KEY_UP)
			{
				keys[UP] = true;
			}
			if (e.keyboard.keycode == ALLEGRO_KEY_DOWN)
			{
				keys[DOWN] = true;
			}
			break;
		}

		// Check keys released this frame
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
			if (e.keyboard.keycode == ALLEGRO_KEY_UP)
			{
				keys[UP] = false;
			}
			if (e.keyboard.keycode == ALLEGRO_KEY_DOWN)
			{
				keys[DOWN] = false;
			}
		}

		// Check if the timer has run out
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

// TODO: Separate the draw calls in updateFrame to their own function, drawFrame!
void Game::updateFrame()
{
	// Ensure the frame isn't updated again before next frame update
	update = false;

	// Do any drawing to the buffer
	al_set_target_bitmap(Game::buffer);
	al_clear_to_color(al_map_rgb(128, 128, 128));

	// Vary drawing procedure based on current game state
	switch (state)
	{
		// TODO: Implement splash screen and title screen!
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
			// Check if formations around the player have been loaded
			bool loadedFormations[6] = { false, false, false, false, false, false };
			for (int i = 0; i < formations.count; i++)
			{
				// If formations are 2048px above the top of the camera, get rid of them, since we're probably not going up that high.
				if (formations[i].y <= camera.y - 2048)
				{
					formations[i].unload();
					formations.remove(i);
					i--;
					continue;
				}

				// Are the formations left, right, and center of the player loaded?
				if ((int)(formations[i].y / 2048.0f) == (int)(player.y / 2048.0f) && player.y >= 2048.0f)
				{
					if ((int)(formations[i].x / 2048.0f) == (int)(player.x / 2048.0f) - 1)
					{
						loadedFormations[0] = true;
					}
					else if ((int)(formations[i].x / 2048.0f) == (int)(player.x / 2048.0f))
					{
						loadedFormations[1] = true;
						player.currentFormation = i;
					}
					else if ((int)(formations[i].x / 2048.0f) == (int)(player.x / 2048.0f) + 1)
					{
						loadedFormations[2] = true;
					}
				}

				// Are the formations down-left, down, and down-right of the player loaded?
				else if ((int)(formations[i].y / 2048.0f) == (int)(player.y / 2048.0f) + 1)
				{
					if ((int)(formations[i].x / 2048.0f) == (int)(player.x / 2048.0f) - 1)
					{
						loadedFormations[3] = true;
					}
					else if ((int)(formations[i].x / 2048.0f) == (int)(player.x / 2048.0f))
					{
						loadedFormations[4] = true;
					}
					else if ((int)(formations[i].x / 2048.0f) == (int)(player.x / 2048.0f) + 1)
					{
						loadedFormations[5] = true;
					}
				}
			}

			// Load in any formations that need loading
			for (int i = 0; i < 6; i++)
			{
				// Don't bother checking the first row if the player's in the grace-chunk
				if (player.y < 2048.0f && i < 3)
				{
					i = 3;
				}
				// This formation needs loading!
				if (!loadedFormations[i])
				{
					formations.push(Formation());
					formations[formations.count - 1].load((((int)player.x / 2048) + ((i % 3) - 1)) * 2048, (((int)player.y / 2048) + (i / 3)) * 2048, obstacleSpr, powerups);
				}
			}

			// Check collisions
			bool colliding = false;
			if(player.currentFormation >= 0)
			{
				// For every object in the formation the player is currently in
				for (int i = 0; i < formations[player.currentFormation].objects.count; i++)
				{
					// Are we colliding with the current object?
					if (formations[player.currentFormation].objects[i].isColliding(player.x, player.y))
					{
						// If so, is it an obstacle?
						if (!formations[player.currentFormation].objects[i].powerup)
						{
							colliding = true;

							// If not currently in invincibility frames, update our status accordingly!
							if (!player.isInvincible)
							{
								int lives = (player.status >> 0x6) & 0x3;
								lives--;

								if (lives < 0)
								{
									lives = 0;
									player.isDead = true;
								}

								lives = lives << 0x6;

								player.status = player.status & 0x3F;
								player.status = player.status | lives;
							}
						}

						// Update our status based on what kind of powerup it was
						else
						{
							// Lightning bolt, shell, paint bucket
							if (formations[player.currentFormation].objects[i].type < 3)
							{
								// Adjust our variables accordingly
								if (formations[player.currentFormation].objects[i].type == 0 && !(player.status & 1))
								{
									player.maxVelocity += 5.0f;
								}
								else if (formations[player.currentFormation].objects[i].type == 1 && !(player.status & 2))
								{
									player.minVelocity /= 2.0f;
								}
								else if(formations[player.currentFormation].objects[i].type == 2)
								{
									player.size += 0.1f;
								}

								player.status = player.status | (int)std::pow(2, formations[player.currentFormation].objects[i].type);
							}

							// Multiplier
							else if(formations[player.currentFormation].objects[i].type == 3)
							{
								int multiplier = (player.status >> 0x3) & 0x7;
								multiplier++;

								if (multiplier > 7)
								{
									multiplier = 7;
								}


								multiplier = multiplier << 0x3;

								player.status = player.status & 0xC7;
								player.status = player.status | multiplier;
							}

							// Lives
							else if (formations[player.currentFormation].objects[i].type == 4)
							{
								int lives = (player.status >> 0x6) & 0x3;
								lives++;

								if (lives > 3)
								{
									lives = 3;
								}

								lives = lives << 0x6;

								player.status = player.status & 0x3F;
								player.status = player.status | lives;
							}

							// Remove the powerup from play
							formations[player.currentFormation].objects.remove(i);
						}
					}
				}
			}

			// If we aren't colliding with any obstacles, remove our invincibility frames!
			if (!colliding)
			{
				player.isInvincible = false;
			}
			else
			{
				player.isInvincible = true;
			}

			// Update the player based on the keyboard state, move the camera to the player's position
			player.update(keys);
			camera.update(player.x - 512, player.y - 64);

			/* DRAW CALLS BEGIN HERE */

			// Set up the shader to draw the infinite BG
			al_use_shader(bgShader.shader);

			float texSize[2] = { (float)al_get_bitmap_width(background), (float)al_get_bitmap_height(background) };
			al_set_shader_float_vector("texSize", 2, texSize, 1);

			al_set_shader_sampler("bg_tex", background, 1);

			float bufferSize[2] = { 1024, 768 };
			al_set_shader_float_vector("bufferSize", 2, bufferSize, 1);

			float cameraPos[2] = { (float)camera.x, (float)camera.y };
			al_set_shader_float_vector("cameraPos", 2, cameraPos, 1);

			// Draw the infinite BG
			al_draw_bitmap(bgBuffer, 0, 0, NULL);

			al_use_shader(NULL);

			// For every formation loaded, draw all of its obstacles
			// TODO: Optimize this so that only obstacles within the bounds of the camera are being drawn!
			for (int i = 0; i < formations.count; i++)
			{
				formations[i].draw(camera);
			}

			// Draw the player
			player.draw(camera);

			// Draw the HUD
			al_draw_text(hudFont[0], al_map_rgb(255, 255, 255), 128, 1, ALLEGRO_ALIGN_CENTRE, "SCORE");
			al_draw_text(hudFont[0], al_map_rgb(255, 255, 255), 900, 1, ALLEGRO_ALIGN_CENTRE, "SIZE");

			al_draw_textf(hudFont[1], al_map_rgb(255, 255, 255), 128, 32, ALLEGRO_ALIGN_CENTRE, "%08d", player.score);
			al_draw_textf(hudFont[1], al_map_rgb(255, 255, 255), 900, 32, ALLEGRO_ALIGN_CENTRE, "%1.6f", player.size);

			// Figure out which images to draw to the HUD based on the player's current status
			for (int i = 0; i < 8; i++)
			{
				if (i < 3)
				{
					if (player.status & (int)std::pow(2, i))
					{
						al_draw_bitmap(powerups[i], 37 + (i * 32), 80, NULL);
					}
				}
				else if (i < 6)
				{
					int multiplier = (player.status >> 0x3) & 0x7;
					if (multiplier)
					{
						al_draw_textf(hudFont[2], al_map_rgb(255, 255, 255), 37 + (i * 32), 80, NULL, "%dX", multiplier + 1);
					}
					i = 6;
				}
				else
				{
					int lives = (player.status >> 0x6) & 0x3;
					if (lives)
					{
						al_draw_bitmap(powerups[i - 3], 37 + ((i - 3) * 32), 80, NULL);
						al_draw_textf(hudFont[2], al_map_rgb(255, 255, 255), 64 + ((i - 3) * 32), 80, NULL, "x%d", lives);
					}
					break;
				}
			}
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
		// TODO: Implement loading for splash and title screens!
		case SPLASH:
		{
			break;
		}
		case TITLE:
		{
			break;
		}

		// TODO: Clean this up, if possible!
		case GAME:
		{
			loadGraphics();
			camera.init();
			player.init();
			bgShader.load(display, "shaders/Vertex Shader", "shaders/BG Pixel Shader");
			hudFont.push(al_load_ttf_font("data/fonts/hud.ttf", 26, NULL));
			hudFont.push(al_load_ttf_font("data/fonts/hud.ttf", 34, NULL));
			hudFont.push(al_load_ttf_font("data/fonts/hudBold.ttf", 22, NULL));

			// Create the formations container, and place the first 3 formations at the row below the player
			for (int i = 0; i < 3; i++)
			{
				formations.push(Formation());
			}
			formations[0].load(-2048, 2048, obstacleSpr, powerups);
			formations[1].load(0, 2048, obstacleSpr, powerups);
			formations[2].load(2048, 2048, obstacleSpr, powerups);

			break;
		}
	}
}

void Game::loadGraphics()
{
	loadBG();
	loadPowerupData();
	loadObstacleData();
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

void Game::loadPowerupData()
{
	std::stringstream convert;
	std::string path;
	for (int i = 0; i < 5; i++)
	{
		path = "data/sprites/powerups/";
		convert << i;
		path += convert.str();
		path += ".png";
		powerups.push(al_load_bitmap(path.c_str()));
		convert.str(std::string());
		convert.clear();
	}
}

void Game::loadObstacleData()
{
	std::stringstream convert;
	std::string path;

	switch (level)
	{
		case 1:
		{
			obstacleSpr.clear();
			for (int i = 0; i < 1; i++)	// TODO: This loop is kind of hacky, fix it later!
			{
				path = "data/sprites/obstacles/";
				convert << i;
				path += convert.str();
				path += ".png";
				obstacleSpr.push(al_load_bitmap(path.c_str()));
				convert.str(std::string());
				convert.clear();
			}
			break;
		}
	}
}

void Game::unloadGraphics()
{
	unloadPowerupData();
	unloadObstacleData();
}

void Game::unloadPowerupData()
{
	for (int i = 0; i < 5; i++)
	{
		al_destroy_bitmap(powerups[i]);
	}
}

void Game::unloadObstacleData()
{
	for (int i = 0; i < 1; i++)
	{
		al_destroy_bitmap(obstacleSpr[i]);
	}
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
			unloadGraphics();
			player.unload();
			bgShader.unload();
			al_destroy_font(hudFont[0]);
			al_destroy_font(hudFont[1]);
			al_destroy_font(hudFont[2]);

			for (int i = 0; i < formations.count; i++)
			{
				formations[i].unload();
			}

			Formation::eraseNumFiles();

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