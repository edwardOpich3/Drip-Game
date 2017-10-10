#include "Formation.h"
#include "FormationReader.h"
#include <fstream>

void Formation::load(int x, int y, ALLEGRO_BITMAP** obstacleSpr, ALLEGRO_BITMAP** powerupSpr)
{
	std::ifstream reader("data/obstacle formations/smile.fmt", std::ios::in | std::ios::binary | std::ios::ate);

	if (reader.is_open())
	{
		this->x = x;
		this->y = y;

		int size = reader.tellg();
		this->numObjects = size / 24;

		reader.seekg(0, std::ios::beg);
		unsigned char temp[4];

		if (objects != nullptr)
		{
			delete[] objects;
			objects = nullptr;
		}
		objects = new GameObject[numObjects];

		for (int i = 0; reader.peek() != -1; i++)
		{
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

			objects[i].width = objects[i].size;
			objects[i].height = objects[i].size * (al_get_bitmap_height(objects[i].sprite) / al_get_bitmap_width(objects[i].sprite));	// Height is always proportional to width

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
	for (int i = 0; i < numObjects; i++)
	{
		objects[i].draw(camera);
	}
}

void Formation::removeObject(int index)
{
	for (int i = index; i < numObjects; i++)
	{
		objects[i] = objects[i + 1];
	}

	numObjects--;
}

void Formation::unload()
{
	if (objects != nullptr)
	{
		delete[] objects;
		objects = nullptr;
	}

	numObjects = 0;
	x = 0;
	y = 0;
}

Formation::Formation()
{
}


Formation::~Formation()
{
}
