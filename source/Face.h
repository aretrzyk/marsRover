#pragma once
#include "Base.h"

class Face
{
public:
	glm::vec3 vertex1;
	glm::vec3 vertex2;
	glm::vec3 vertex3;

	glm::vec3 normal;

	Face();
	Face(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 normal);
};

