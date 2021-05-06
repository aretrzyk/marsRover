#pragma once
#include "OBJLoader.h"
#include "Shader.h"
//#include "Texture.h"

class Game;

class Object
{
private:


	Shader* shader;
	//Texture texture;

	unsigned int verticesCount;

	//to samo co unsigned int
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 posVec;
	glm::vec3 rotationVec;
	glm::vec3 scaleVec;

	glm::mat4 modelMatrix;

	glm::vec3 lightPos;

	void updateModelMatrix();

public:
	Object();
	void move(glm::vec3 vec);
	void rotate(glm::vec3 vec);
	void scale(glm::vec3 vec);

	void setColor(glm::vec3 color);
	void setColor(glm::vec4 color);

	void load(std::vector<Vertex>& vertices);

	void draw();

};

