#pragma once
class Camera
{
public:

	int x, y;
	int width, height;

	void init();
	void update(int x, int y);

	Camera();
	~Camera();
};

