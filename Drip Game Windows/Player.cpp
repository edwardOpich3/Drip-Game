#include "Player.h"
#include "Input.h"
#include <math.h>

// Enums
enum ANIMATION_STATE { IDLE, TURNING, HIT };	// Indices of the players animation states. Currently Unused.

const int Player::trailNum;

void Player::init()
{
	position = Vector2(1024.0f, -1024.0f);
	size = Vector2(32.0f, 64.0f);
	angle = 0.0f;							// Downwards
	maxAngle = 45.0f, minAngle = -45.0f;	// Max turn is a 45 degree angle in either direction
	velocity = 7.0f;
	minVelocity = 6.0f, midVelocity = 9.0f, maxVelocity = 12.0f;
	acceleration = 0.1f;
	scale = 1.0f;
	score = 0;
	status = 0;
	isDead = false;
	isInvincible = false;

	currentFormation = -1;

	// Say no to memory leaks; only load a bitmap if its destination isn't currently occupied
	if (!sprite)
	{
		sprite = al_load_bitmap("data/sprites/player.png");
	}
	frame = 0;
	animationState = IDLE;

	if (!trail)
	{
		trail = al_load_bitmap("data/sprites/trail.png");
	}
	for (int i = 0; i < trailNum; i++)
	{
		trailPos[i] = Vector2();
		trailAngle[i] = 0;
		trailSize[i] = 0;
	}
}

void Player::unload()
{
	al_destroy_bitmap(sprite);
	sprite = nullptr;

	al_destroy_bitmap(trail);
	trail = nullptr;
}

void Player::draw(Camera camera)
{
	for (int i = trailNum - 1; i >= 0; i--)
	{
		al_draw_scaled_rotated_bitmap(trail, (al_get_bitmap_width(trail) / 2.0f), (al_get_bitmap_height(trail) / 2.0f), trailPos[i].x - camera.position.x, trailPos[i].y - camera.position.y, (trailSize[i] * size.x) / al_get_bitmap_width(sprite), (trailSize[i] * size.y) / al_get_bitmap_height(sprite), -trailAngle[i] * (ALLEGRO_PI / 180.0f), NULL);
	}
	al_draw_scaled_rotated_bitmap(sprite, (al_get_bitmap_width(sprite) / 2.0f), (al_get_bitmap_height(sprite) / 2.0f), position.x - camera.position.x, position.y - camera.position.y, (scale * size.x) / al_get_bitmap_width(sprite), (scale * size.y) / al_get_bitmap_height(sprite), -angle * (ALLEGRO_PI / 180.0f), NULL);
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
		if (position.y > 0)
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
		trailPos[i] = trailPos[i - 1];
		trailAngle[i] = trailAngle[i - 1];
		trailSize[i] = trailSize[i - 1];
	}

	// The first paint trail particle will be at the player's soon-to-be prior position
	trailPos[0] = position;
	trailAngle[0] = angle;
	trailSize[0] = scale;

	// Update position (TODO: Velocity should be implemented as a vector!)
	position.x += sin(angle * (ALLEGRO_PI / 180.0f)) * velocity;
	position.y += cos(angle * (ALLEGRO_PI / 180.0f)) * velocity;

	// Check keys!
	if (position.y > 0)
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
	if (position.y > 0)
	{
		// TODO: Update how score is calculated! Make sure it matches exactly what you want!
		score += scale * velocity * (((status >> 0x3) & 0x7) + 1);
	}
}

Player::Player()
{
}


Player::~Player()
{
}
