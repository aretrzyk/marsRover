#pragma once
#include "Map.h"

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
	float pitch;
	float roll;

	float speed;
	float maxSpeed;
	float acceleration;
	float deceleration;
	float drag;
	float wheelYaw;
	float wheelBase;
	float wheelDistance;
	float friction;

	glm::vec3 lastFrontLeftWheelPos;
	glm::vec3 lastFrontRightWheelPos;
	glm::vec3 lastMiddleLeftWheelPos;
	glm::vec3 lastMiddleRightWheelPos;
	glm::vec3 lastBackLeftWheelPos;
	glm::vec3 lastBackRightWheelPos;

	Map* map;

	float wheelRadius;

	void setY(float y);

	void initObjects(OBJLoader& loader);
	void drawObjects();
	void update();
	void rotateWheels();

	void rotYaw(float angle);
	void setYaw(float angle);

	void setPitch(float angle);

	void setRoll(float angle);

	void turnLeft();
	void turnRight();

	bool keyDown(int key);

public:
	Player(OBJLoader& loader, Map* map);
	~Player();

	glm::vec3 getOrigin();
	float getYaw();

	void move(glm::vec3 vec);
	void setPos(glm::vec3 vec);
	void draw();
};

