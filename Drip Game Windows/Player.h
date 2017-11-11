#pragma once
#include "allegro5/allegro.h"
#include "Camera.h"
class Player
{
public:

	float x, y;				// Position in the level in pixels. Not screen coordinates.
	float width, height;	// Width and height of the player; used for bitmap drawing and collision calculations
	float angle;			// Angle the player is rotated at, in degrees.

	float maxAngle, minAngle;						// Maximum and minimum angles of rotation. Determines how fast left and right the player can move.
	float velocity;									// Current pixels per second. This isn't just the y component, this is total velocity.
	float minVelocity, midVelocity, maxVelocity;	// Pixels per second, variable due to powerups. midVelocity is the speed the player floats around neutrally.
	float acceleration;								// Pixels per second^2. How fast the player can manually change speed.
	float size;										// Stored as scale, with 1.0f being 1x size, 2.0f being 2x size, 0.5f being half size, etc.
	int score;										// A given, the score. Calculated based on many things.
	char status;									// Use this as a flag, as it's essentially an array of 8 bools. Contains the player's current powerups.
	bool isDead;									// Has the player collided with something?
	bool isInvincible;								// If the player collided with something with an extra life, this is set til they stop colliding with the object.

	int currentFormation;	// The index of the formation the player is currently in.

	ALLEGRO_BITMAP* sprite = nullptr;	// The player's spritesheet
	char frame;							// The current frame of animation. Currently unused.
	char animationState;				// The current animation state; moving, turning, dying, etc. Currently unused.

	ALLEGRO_BITMAP* trail = nullptr;	// The player's trail, pasted multiple times
	static const int trailNum = 30;		// The number of trail sprites to put behind the player

	// The previous x and y positions to paste the trail at, as well as the angle and size
	float trailX[trailNum];
	float trailY[trailNum];
	float trailAngle[trailNum];
	float trailSize[trailNum];

	void init();				// Initializes the player and loads any necessary data.
	void unload();				// Unloads anything necessary from memory.
	void draw(Camera camera);	// Draws the player to the screen
	void update();				// Updates the player's position and stuff

	Player();
	~Player();
};

