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

	glm::vec3 pos;
	float yaw;
	float speed;
	float maxSpeed;
	float acceleration;
	float deceleration;
	float drag;
	float wheelYaw;
	float wheelBase;
	float friction;

	glm::vec3 lastFrontLeftWheelPos;

	float wheelRadius;


	void initObjects(OBJLoader& loader);
	void drawObjects();
	void update();
	void rotateWheels();

	void rotYaw(float angle);
	void setRotYaw(float angle);

	void turnLeft();
	void turnRight();

	bool keyDown(int key);

public:
	Player(OBJLoader& loader);
	~Player();

	glm::vec3 getOrigin();
	float getYaw();

	void move(glm::vec3 vec);
	void setPos(glm::vec3 vec);
	void draw();
};

