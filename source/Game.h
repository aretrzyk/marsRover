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

	Map* map;
	Object* sun;
	Player* rover;

	unsigned int cameraType;

	void updateInput();

	void objectsInit();
	void drawObjects();

public:
	Game();
	~Game();
	void run();
};

