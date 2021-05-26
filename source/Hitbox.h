#pragma once
#include "Base.h"

class OBJLoader;
class Object;

class Hitbox
{
private:
	float xMin;
	float xMax;
	float yMin;
	float yMax;
	float zMin;
	float zMax;
	glm::vec3 size;
	glm::vec3 origin;

public:
	Hitbox();

	bool checkCollision();

	glm::vec3 getOrigin();
	glm::vec3 getSize();


	friend OBJLoader;
	friend Object;
};