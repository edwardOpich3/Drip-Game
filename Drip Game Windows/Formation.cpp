#include "Formation.h"
#include "FormationReader.h"
#include <fstream>

void Formation::load(int x, int y, ALLEGRO_BITMAP** obstacleSpr, ALLEGRO_BITMAP** powerupSpr)
{
	// Hard-coded formation, later replace this with a random selection algorithm
	std::ifstream reader("data/obstacle formations/smile.fmt", std::ios::in | std::ios::binary);

	// This function won't work if the path passed to the reader is invalid!
	if (reader.is_open())
	{
		// Set formation's position
		this->x = x;
		this->y = y;

		unsigned char temp[4];

		// If the formation was already defined but for some reason not unloaded, delete the object container
		objects.clear();

		// Load each object into the formation
		for (int i = 0; reader.peek() != -1; i++)
		{
			objects.push(GameObject());

			// Powerup?
			reader.read((char*)temp, 4);
			objects[i].powerup = FormationReader::readInt32(temp);

			// Object Type
			reader.read((char*)temp, 4);
			objects[i].type = FormationReader::readInt32(temp);

			// X and Y Coords (center of the object)
			reader.read((char*)temp, 4);
			objects[i].x = FormationReader::readInt32(temp) + x;

			reader.read((char*)temp, 4);
			objects[i].y = FormationReader::readInt32(temp) + y;

			// Scale (1 == 128 width)
			reader.read((char*)temp, 4);
			objects[i].size = FormationReader::readSingle(temp);

			// Angle (0 is pointing down)
			reader.read((char*)temp, 4);
			objects[i].angle = FormationReader::readSingle(temp);

			// Sprite (based on type)
			if (!objects[i].powerup)
			{
				objects[i].sprite = obstacleSpr[objects[i].type];
			}
			else
			{
				objects[i].sprite = powerupSpr[objects[i].type];
			}

			// Set the object's width and height based on size
			objects[i].width = objects[i].size;
			objects[i].height = objects[i].size * (al_get_bitmap_height(objects[i].sprite) / al_get_bitmap_width(objects[i].sprite));	// Height is always proportional to width

			// If the object is an obstacle, the base width should be 128, otherwise it should be 32.
			if (!objects[i].powerup)
			{
				objects[i].width *= 128.0f;
				objects[i].height *= 128.0f;
			}
			else
			{
				objects[i].width *= 32.0f;
				objects[i].height *= 32.0f;
			}
		}
		reader.close();
	}
}

void Formation::draw(Camera camera)
{
	for (int i = 0; i < objects.count; i++)
	{
		objects[i].draw(camera);
	}
}

void Formation::unload()
{
	objects.clear();
}

Formation::Formation()
{
}


Formation::~Formation()
{
}
