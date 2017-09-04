#pragma once
#include "allegro5\allegro.h"
class Shader
{
public:
	
	ALLEGRO_SHADER *bgShader;

	bool load(ALLEGRO_DISPLAY* display);
	void unload();

	Shader();
	~Shader();
};

