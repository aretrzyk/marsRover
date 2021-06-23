#include "Face.h"

Face::Face()
{
	this->vertex1 = glm::vec3(0.f);
	this->vertex2 = glm::vec3(0.f);
	this->vertex3 = glm::vec3(0.f);
	this->normal = glm::vec3(0.f);
}

Face::Face(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 normal)
{
	this->vertex1 = v1;
	this->vertex2 = v2;
	this->vertex3 = v3;
	this->normal = normal;
}
