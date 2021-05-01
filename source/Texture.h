#pragma once
#include "Shader.h"
#include "SOIL2/SOIL2.h"
#include "string"


class Texture
{
private:
	unsigned int texture;

public:
	Texture(std::string path);
	void use();
	void unuse();
};

