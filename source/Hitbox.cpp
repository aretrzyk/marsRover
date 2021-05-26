#include "Hitbox.h"

Hitbox::Hitbox()
{
	this->xMin = 0;
	this->xMax = 0;
	this->yMin = 0;
	this->yMax = 0;
	this->zMin = 0;
	this->zMax = 0;

	this->size = glm::vec3(0);
	this->origin = glm::dvec3(0);
}


bool Hitbox::checkCollision()
{
	if (this->yMin <= 0) return true;
	return false;
}

glm::vec3 Hitbox::getOrigin()
{
	return this->origin;
}

glm::vec3 Hitbox::getSize()
{
	return this->size;
}
