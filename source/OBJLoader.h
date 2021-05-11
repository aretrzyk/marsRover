#pragma once
#include "Vertex.h"
#include "Hitbox.h"

class OBJLoader
{
private:
	std::vector<std::vector<Vertex>> vertices;
	std::vector<std::string> names;
	
	std::vector<Hitbox> hitboxes;

	std::vector<glm::vec3> pos;
	std::vector<glm::vec2> texcoords;
	std::vector<glm::vec3> normals;

	std::vector<GLuint> posElements;
	std::vector<GLint> texcoordsElements;
	std::vector<GLuint> normalsElements;

	void buildMesh();

public:
	OBJLoader(std::string path);
	//one object
	std::vector<Vertex>& getVertices();
	Hitbox& getHitboxes();
	//when you have kilka objects in file
	std::vector<Vertex>& getVertices(std::string name);
	Hitbox& getHitboxes(std::string name);
	
};
