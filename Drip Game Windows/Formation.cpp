#include "Formation.h"
#include <fstream>
#include <sstream>

int Formation::numFiles = 0;

void Formation::load(int x, int y, Container<ALLEGRO_BITMAP*> obstacleSpr, Container<ALLEGRO_BITMAP*> powerupSpr)
{
	// If we haven't gotten the number of files yet, we need to do that!
	if (numFiles < 1)
	{
		getNumFiles();
	}

	// Using the number of files as our upper limit, randomly select one of them to load!
	// TODO: Instead of loading the files in at runtime, try loading them all into a container at load time, and then copying from there at runtime
	std::stringstream convert;
	std::string path = "data/obstacle formations/";
	convert << (((unsigned int)rand() % numFiles) + 1);
	path += convert.str();
	path += ".fmt";

	std::ifstream reader(path, std::ios::in | std::ios::binary);

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
			objects[i].powerup = *reinterpret_cast<int*>(temp);

			// Object Type
			reader.read((char*)temp, 4);
			objects[i].type = *reinterpret_cast<int*>(temp);

			// X and Y Coords (center of the object)
			reader.read((char*)temp, 4);
			objects[i].x = *reinterpret_cast<int*>(temp) + x;

			reader.read((char*)temp, 4);
			objects[i].y = *reinterpret_cast<int*>(temp) + y;

			// Scale (1 == 128 width)
			reader.read((char*)temp, 4);
			objects[i].size = *reinterpret_cast<float*>(temp);

			// Angle (0 is pointing down)
			reader.read((char*)temp, 4);
			objects[i].angle = *reinterpret_cast<float*>(temp);

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

void Formation::getNumFiles()
{
	std::stringstream convert;
	std::string path = "data/obstacle formations/";
	convert << (numFiles + 1);
	path += convert.str();
	path += ".fmt";
	std::fstream check(path);

	while (check.good())
	{
		numFiles++;
		check.close();
		convert.str(std::string());
		convert.clear();

		path = "data/obstacle formations/";
		convert << (numFiles + 1);
		path += convert.str();
		path += ".fmt";

		check.open(path);
	}
}

void Formation::eraseNumFiles()
{
	numFiles = 0;
}

Formation Formation::operator=(const Formation& other)
{
	x = other.x;
	y = other.y;
	objects = other.objects;
	return *this;
}

Formation::Formation()
{
}

Formation::Formation(const Formation& other)
{
	x = other.x;
	y = other.y;
	objects = other.objects;
}

Formation::~Formation()
{
}
