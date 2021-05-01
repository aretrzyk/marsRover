#pragma once
#include <istream>
#include <sstream>
#include <vector>
#include "Shader.h"
//#include "Texture.h"

class Object
{
private:
	std::vector<glm::vec3> verticles;
	std::vector<GLuint> elements;

	Shader* shader;
	//Texture texture;

	//to samo co unsigned int
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 translationVec;
	glm::vec3 rotationVec;
	glm::vec3 scaleVec;

	glm::mat4 modelMatrix;


public:
	Object();
	void move(glm::vec3 vec);
	void rotate(glm::vec3 vec);
	void scale(glm::vec3 vec);

	void loadFromFile(std::string path);

	void draw(glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix);

};

