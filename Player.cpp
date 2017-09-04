#include "Player.h"
#include <math.h>

enum POWERUPS { MULTIPLIER, SPEED_UP, SPEED_DOWN };
enum ANIMATION_STATE { IDLE, TURNING, HIT };
enum KEYS { LEFT, RIGHT };

const int Player::trailNum;

void Player::init()
{
	x = 512.0f, y = -512.0f;
	width = 32.0f, height = 64.0f;
	angle = 270.0f;	// Downwards, 0 being to the right
	maxAngle = 315.0f, minAngle = 225.0f;	// Max is right, min is full left; balance this later
	velocity = 7.0f;
	minVelocity = 5.0f, maxVelocity = 10.0f;
	acceleration = 1.0f;
	size = 1.0f;
	time = 0.0f;
	score = 0;
	status = 0;

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
		al_draw_scaled_rotated_bitmap(trail, (al_get_bitmap_width(trail) / 2.0f), (al_get_bitmap_height(trail) / 2.0f), trailX[i] - camera.x, trailY[i] - camera.y, trailSize[i] * (height / al_get_bitmap_width(sprite)), trailSize[i] * (width / al_get_bitmap_height(sprite)), -trailAngle[i] * (ALLEGRO_PI / 180.0f), NULL);
	}
	al_draw_scaled_rotated_bitmap(sprite, (al_get_bitmap_width(sprite) / 2.0f), (al_get_bitmap_height(sprite) / 2.0f), x - camera.x, y - camera.y, size * (height / al_get_bitmap_width(sprite)), size * (width/ al_get_bitmap_height(sprite)), -angle * (ALLEGRO_PI / 180.0f), NULL);
}

void Player::update(bool* keys, Camera camera)
{
	for (int i = trailNum - 1; i > 0; i--)
	{
		trailX[i] = trailX[i - 1];
		trailY[i] = trailY[i - 1];
		trailAngle[i] = trailAngle[i - 1];
		trailSize[i] = trailSize[i - 1];
	}

	trailX[0] = x;
	trailY[0] = y;
	trailAngle[0] = angle;
	trailSize[0] = size;

	x += sin((angle - 270.0f) * (ALLEGRO_PI / 180.0f)) * velocity;
	y += cos((angle - 270.0f) * (ALLEGRO_PI / 180.0f)) * velocity; // Add this when vertical movement is added.

	/*if (x < 0)
	{
		x = 0;
	}
	else if (x > 1024)
	{
		x = 1024;
	}*/

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

	draw(camera);
}

Player::Player()
{
}


Player::~Player()
{
}
