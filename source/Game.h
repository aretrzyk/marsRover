#pragma once
#include "Player.h"
#include "Camera.h"

class Game
{
private:
	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;
	//rozmiar pojedyñczej klatki
	int framebufferWidth;
	int framebufferHeight;

	//Kamera
	Camera* camera;

	Object* floor;
	Object* sun;
	Player* rover;

	float test = 0;

	void objectsInit();
	void drawObjects();

public:
	Game();
	~Game();
	void run();

	glm::vec3 getLightPos()const;
	glm::vec3 getLightColor()const;
};

