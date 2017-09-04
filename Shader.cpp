#include "Shader.h"
#include <iostream>

bool Shader::load(ALLEGRO_DISPLAY* display)
{
	bgShader = al_create_shader(ALLEGRO_SHADER_AUTO);
	if(!bgShader)
	{
		return false;
	}

	// OpenGL Shader
	if (al_get_shader_platform(bgShader) == ALLEGRO_SHADER_GLSL)
	{
		al_attach_shader_source_file(bgShader, ALLEGRO_VERTEX_SHADER, "shaders/Vertex Shader.glsl");
		al_attach_shader_source_file(bgShader, ALLEGRO_PIXEL_SHADER, "shaders/BG Pixel Shader.glsl");
	}

	// Direct3D Shader
	else
	{
		al_attach_shader_source_file(bgShader, ALLEGRO_VERTEX_SHADER, "shaders/Vertex Shader.hlsl");
		al_attach_shader_source_file(bgShader, ALLEGRO_PIXEL_SHADER, "shaders/BG Pixel Shader.hlsl");
	}

	if (!al_build_shader(bgShader))
	{
		std::cout << al_get_shader_log(bgShader);
		std::cin.get();
		std::cin.get();
		return false;
	}

	std::cout << al_get_shader_log(bgShader);

	return true;
}

void Shader::unload()
{
	al_destroy_shader(bgShader);
}

Shader::Shader()
{
}


Shader::~Shader()
{
}
