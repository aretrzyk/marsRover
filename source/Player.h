#pragma once
#include "Base.h"
#include "Object.h"
class Player
{
private:
	Object body;
	Object head;
	Object frontLeftWheel;
	Object frontRightWheel;
	Object middleLeftWheel;
	Object middleRightWheel;
	Object backLeftWheel;
	Object backRightWheel;

	void loadObjects(OBJLoader loader);
	void drawObjects();

public:
	Player(OBJLoader loader);
	Player(std::vector<Vertex>& vertices);

	void draw();
};