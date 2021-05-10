#pragma once
#include "Object.h"

class Player{
private:
	Object* head;
	Object* body;
	Object* frontLeftWheel;
	Object* frontRightWheel;
	Object* middleLeftWheel;
	Object* middleRightWheel;
	Object* backLeftWheel;
	Object* backRightWheel;

	void initObjects(OBJLoader& loader);
	void drawObjects();

public:
	Player(OBJLoader& loader);
	~Player();
	void move(glm::vec3 vec);
	void draw();
};

