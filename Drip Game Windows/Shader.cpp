#include "Shader.h"
#include <iostream>

bool Shader::load(ALLEGRO_DISPLAY* display, std::string vertexPath, std::string pixelPath)
{
	// Create shader based on current display type
	shader = al_create_shader(ALLEGRO_SHADER_AUTO);
	if(!shader)
	{
		return false;
	}

	// OpenGL Shader
	if (al_get_shader_platform(shader) == ALLEGRO_SHADER_GLSL)
	{
		vertexPath += ".glsl";
		pixelPath += ".glsl";
	}

	// Direct3D Shader
	else
	{
		vertexPath += ".hlsl";
		pixelPath += ".hlsl";
	}

	// Try to put the vertex and pixel shader source files in memory, output debug info on fail
	if (!al_attach_shader_source_file(shader, ALLEGRO_VERTEX_SHADER, vertexPath.c_str()))
	{
		std::cout << al_get_shader_log(shader);
		std::cin.get();
		return false;
	}
	if (!al_attach_shader_source_file(shader, ALLEGRO_PIXEL_SHADER, pixelPath.c_str()))
	{
		std::cout << al_get_shader_log(shader);
		std::cin.get();
		return false;
	}

	// Attempt to build the shader object, output debug info on fail
	if (!al_build_shader(shader))
	{
		std::cout << al_get_shader_log(shader);
		std::cin.get();
		return false;
	}

	return true;
}

void Shader::unload()
{
	al_destroy_shader(shader);
	shader = nullptr;
}

Shader::Shader()
{
}


Shader::~Shader()
{
}
