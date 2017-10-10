#pragma once
#include "allegro5/allegro.h"
#include "Camera.h"
class Player
{
public:

	float x, y;	// Position in the level in pixels. Emphasis on "in the level", not "on the screen".
	float width, height;	// Width and height of the player; used for bitmap drawing and collision calculations
	float angle;	// Stored as degrees, the superior angle measurement and no one will convince me otherwise ;)

	float maxAngle, minAngle;	// Maximum and minimum angles of rotation. Determines how fast left and right the player can move.
	float velocity;	// Current pixels per second. This isn't just the y component, this is total velocity. Use trig to get components until i get less lazy and make a vector object
	float minVelocity, maxVelocity;	// Pixels per second, variable due to powerups
	float acceleration;	// Pixels per second^2, varies based on powerups. How fast the player can manually change speed, or how fast the drip accelerates at level start.
	float size;	// Stored as scale, with 1.0f being 1x size, 2.0f being 2x size, 0.5f being half size, etc.
	float time;	// In seconds, do the required conversions for the UI
	int score;	// A given, the score. Calculated based on many things, see the brainstorm doc.
	char status;	// Use this as a flag, as it's essentially an array of 8 bools

	int currentFormation;	// The index of the formation the player is currently in.

	ALLEGRO_BITMAP* sprite;	// The player's spritesheet
	char frame;	// The current frame of animation.
	char animationState;	// The current animation state; moving, turning, dying, etc.

	ALLEGRO_BITMAP* trail;	// The player's trail, pasted multiple times
	static const int trailNum = 20;	// The number of trail sprites to put behind the player

	// The previous x and y positions to paste the trail at, as well as the angle and size
	float trailX[trailNum];
	float trailY[trailNum];
	float trailAngle[trailNum];
	float trailSize[trailNum];

	void init();	// Initializes the player and loads any necessary data.
	void unload();	// Unloads anything necessary from memory.
	void draw(Camera camera);	// Draws the player to the screen
	void update(bool* keys);	// Updates the player's position and stuff

	Player();
	~Player();
};

