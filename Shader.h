#pragma once
#include "allegro5\allegro.h"
#include <string>
class Shader
{
public:
	
	ALLEGRO_SHADER *shader;

	// Don't pass extensions, the function will handle those
	bool load(ALLEGRO_DISPLAY* display, std::string vertexPath, std::string pixelPath);
	void unload();

	Shader();
	~Shader();
};

