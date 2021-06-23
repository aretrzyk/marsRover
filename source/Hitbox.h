#pragma once
#include "Base.h"

class OBJLoader;
class Object;
class CubeColider;

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
	glm::vec3 getMin();
	glm::vec3 getMax();


	friend OBJLoader;
	friend Object;
	friend CubeColider;
};