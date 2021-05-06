#pragma once
#include "Vertex.h"

class OBJLoader
{
private:
	std::vector<Vertex> vertices;

	std::vector<glm::vec3> pos;
	std::vector<glm::vec2> texcoords;
	std::vector<glm::vec3> normals;

	std::vector<GLuint> posElements;
	std::vector<GLint> texcoordsElements;
	std::vector<GLuint> normalsElements;

public:
	OBJLoader(std::string path);
	std::vector<Vertex>& getVertices();
	
};
