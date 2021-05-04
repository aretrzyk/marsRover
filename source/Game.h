#pragma once
#include "Camera.h"
#include "Shader.h"
#include "Object.h"


class Game
{
private:
	GLFWwindow* window;
	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;
	//rozmiar pojedyñczej klatki
	int framebufferWidth;
	int framebufferHeight;

	//Kamera
	Camera* camera;

	Object* test;

public:
	Game();
	GLFWwindow* getWindow();
	void run();

};

