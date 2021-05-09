#pragma once
#include "Player.h"
#include "Camera.h"

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
	Object* floor;
	Object* sun;
	Player* rover;

	void objectsInit();
	void drawObjects();

public:
	Game();
	~Game();
	GLFWwindow* getWindow();
	void run();

	glm::vec3 getLightPos()const;
	glm::vec3 getLightColor()const;
};

