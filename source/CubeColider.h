#pragma once
#include "OBJLoader.h"
#include "Map.h"

class CubeColider
{
private:
	Hitbox hitbox;
	Face* faces;

	glm::mat4 matrix;
	glm::vec3 pos;
	glm::vec3 rotation;

	
public:
	CubeColider(Hitbox hitbox);
	~CubeColider();

};

