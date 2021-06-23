#pragma once
#include "Base.h"

class HeightMap
{
private:
	unsigned int** map;

	unsigned int pixelsHeight;
	unsigned int pixelsWidth;

	unsigned int minBright;
	unsigned int maxBright;

	float minHeight;
	float maxHeight;

	glm::vec2 minXZ;
	glm::vec2 maxXZ;

	float sizeX;
	float sizeZ;


public:
	HeightMap(std::string path, glm::vec3 min, glm::vec3 max);

	float getHeight(float x, float z);

};