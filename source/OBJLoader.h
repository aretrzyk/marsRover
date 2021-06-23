#pragma 
#include "Hitbox.h"
#include "Vertex.h"
#include "Face.h"

class OBJLoader
{
private:
	std::vector<std::vector<Vertex>> vertices;
	std::vector<std::string> names;
	
	bool firstHitbox = true;
	Hitbox mainHitbox;
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
	
	std::vector<Vertex>& getVertices();
	Hitbox& getHitboxes();
	std::vector<Face> getFaces();
	Hitbox& getMainHitbox();

	std::vector<Vertex>& getVertices(std::string name);
	Hitbox& getHitboxes(std::string name);
};
