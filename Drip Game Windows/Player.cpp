#include "Player.h"
#include "Input.h"
#include <math.h>

// Enums
enum POWERUPS { MULTIPLIER = 3, FAST = 4, SLOW = 8, SIZE = 16, TIME = 32, LIFE = 192 };	// TODO: Is this even used? Get rid of it if not!
enum ANIMATION_STATE { IDLE, TURNING, HIT };	// Indices of the players animation states. Not yet implemented.

const int Player::trailNum;

void Player::init()
{
	x = 1024.0f, y = -1024.0f;
	width = 32.0f, height = 64.0f;
	angle = 0.0f;	// Downwards
	maxAngle = 45.0f, minAngle = -45.0f;	// Max turn is a 45 degree angle in either direction
	velocity = 7.0f;
	minVelocity = 6.0f, midVelocity = 9.0f, maxVelocity = 12.0f;
	acceleration = 0.1f;
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

void Player::update()
{
	// If the player is dead, make sure they don't move! The game is over!
	if (isDead)
	{
		velocity = 0.0f;
		return;
	}

	// Otherwise, accelerate the drip!
	else
	{
		if (y > 0)
		{
			// Try to slow down if we're pressing up!
			if (Input::keys[Input::UP])
			{
				velocity -= acceleration;
			}

			// Try to speed up if we're pressing down!
			if (Input::keys[Input::DOWN])
			{
				velocity += acceleration;
			}
		}

		// If we're not pressing up or down, we should gravitate to our default speed
		if (!(Input::keys[Input::UP] || Input::keys[Input::DOWN]))
		{
			if (velocity > midVelocity)
			{
				velocity -= acceleration;
				if (velocity < midVelocity)
				{
					velocity = midVelocity;
				}
			}
			else if (velocity < midVelocity)
			{
				velocity += acceleration;
				if (velocity > midVelocity)
				{
					velocity = midVelocity;
				}
			}
		}

		// We should never travel faster than our max velocity
		if (velocity > maxVelocity)
		{
			velocity = maxVelocity;
		}

		// If we're going slower than our minimum velocity, that is unacceptable!
		// TODO: If we have the drip travel backwards at all, this needs fixing!
		else if (velocity < minVelocity)
		{
			velocity = minVelocity;
		}
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
	if (y > 0)
	{
		if (Input::keys[Input::LEFT])
		{
			angle -= 5.0f;
			if (angle < minAngle)
			{
				angle = minAngle;
			}
		}
		if (Input::keys[Input::RIGHT])
		{
			angle += 5.0f;
			if (angle > maxAngle)
			{
				angle = maxAngle;
			}
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
