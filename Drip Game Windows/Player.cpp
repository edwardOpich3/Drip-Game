#include "Player.h"
#include <math.h>

// Enums
enum POWERUPS { MULTIPLIER = 3, FAST = 4, SLOW = 8, SIZE = 16, TIME = 32, LIFE = 192 };	// TODO: Is this even used? Get rid of it if not!
enum ANIMATION_STATE { IDLE, TURNING, HIT };	// Indices of the players animation states. Not yet implemented.
enum KEYS { LEFT, RIGHT };						// Keycodes of keys pressed (TODO: This probably belongs in a keyboard class or something)

const int Player::trailNum;

void Player::init()
{
	x = 1024.0f, y = -512.0f;
	width = 32.0f, height = 64.0f;
	angle = 0.0f;	// Downwards
	maxAngle = 45.0f, minAngle = -45.0f;	// Max turn is a 45 degree angle in either direction
	velocity = 7.0f;
	minVelocity = 5.0f, maxVelocity = 10.0f;
	acceleration = 1.0f;
	size = 1.0f;
	time = 0.0f;
	score = 0;
	status = 0;

	currentFormation = -1;

	sprite = al_load_bitmap("data/sprites/player.png");
	frame = 0;
	animationState = IDLE;

	trail = al_load_bitmap("data/sprites/trail.png");
	for (int i = 0; i < trailNum; i++)
	{
		trailX[i] = 0;
		trailY[i] = 0;
		trailAngle[i] = 0;
		trailSize[i] = 0;
	}
}

void Player::unload()
{
	al_destroy_bitmap(sprite);
}

void Player::draw(Camera camera)
{
	for (int i = trailNum - 1; i >= 0; i--)
	{
		al_draw_scaled_rotated_bitmap(trail, (al_get_bitmap_width(trail) / 2.0f), (al_get_bitmap_height(trail) / 2.0f), trailX[i] - camera.x, trailY[i] - camera.y, (trailSize[i] * width) / al_get_bitmap_width(sprite), (trailSize[i] * height) / al_get_bitmap_height(sprite), -trailAngle[i] * (ALLEGRO_PI / 180.0f), NULL);
	}
	al_draw_scaled_rotated_bitmap(sprite, (al_get_bitmap_width(sprite) / 2.0f), (al_get_bitmap_height(sprite) / 2.0f), x - camera.x, y - camera.y, (size * width) / al_get_bitmap_width(sprite), (size * height) / al_get_bitmap_height(sprite), -angle * (ALLEGRO_PI / 180.0f), NULL);
}

void Player::update(bool* keys)
{
	// If the player is dead, make sure they don't move! The game is over!
	if (isDead)
	{
		velocity = 0.0f;
	}

	// Update the paint trail particles
	for (int i = trailNum - 1; i > 0; i--)
	{
		trailX[i] = trailX[i - 1];
		trailY[i] = trailY[i - 1];
		trailAngle[i] = trailAngle[i - 1];
		trailSize[i] = trailSize[i - 1];
	}

	// The first paint trail particle will be at the player's soon-to-be prior position
	trailX[0] = x;
	trailY[0] = y;
	trailAngle[0] = angle;
	trailSize[0] = size;

	// Update position
	x += sin(angle * (ALLEGRO_PI / 180.0f)) * velocity;
	y += cos(angle * (ALLEGRO_PI / 180.0f)) * velocity;

	/*if (x < 0)
	{
		x = 0;
	}
	else if (x > 1024)
	{
		x = 1024;
	}*/

	// Check keys!
	if (keys[LEFT])
	{
		angle -= 5.0f;
		if (angle < minAngle)
		{
			angle = minAngle;
		}
	}
	if (keys[RIGHT])
	{
		angle += 5.0f;
		if (angle > maxAngle)
		{
			angle = maxAngle;
		}
	}

	// Don't update the score unless the player is on the screen!
	if (y > 0)
	{
		score += size * velocity * (((status >> 0x3) & 0x7) + 1);
	}
}

Player::Player()
{
}


Player::~Player()
{
}
