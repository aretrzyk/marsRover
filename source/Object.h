#pragma once
#include "OBJLoader.h"
#include "Shader.h"
//#include "Texture.h"

class Object
{
private:

	Shader* shader;
	Shader* shaderHitbox;
	//Texture texture;

	unsigned int verticesCount;

	GLuint VAO;
	GLuint VBO;
	GLuint hitboxVBO;

	glm::vec4 objectColor;

	glm::mat4 modelMatrix;
	glm::mat4 rotByOriginMatrix;

	glm::vec3 posVec;
	glm::vec3 scaleVec;

	glm::vec3 rotVec;
	glm::vec3 rotByOriginVec;
	//TODO: add if needed
	//glm::vec3 vecRotByPoint; 
	

	glm::vec3 lightPos;

	Hitbox hitbox;

	int hitboxIndicesNumber;
	glm::vec4 hitboxColor;

	void loadHitbox();
	void updateModelMatrix();

public:
	

	Object();
	Object(std::vector<Vertex> vertices, Hitbox hitbox);
	~Object();

	void load(std::vector<Vertex> vertices);

	void setColor(glm::vec3 color);
	void setColor(glm::vec4 color);

	void move(glm::vec3 vec);
	void setPos(glm::vec3 vec);

	void rot(glm::vec3 angles);
	void setRot(glm::vec3 angles);
	void rotByOrigin(glm::vec3 angles);
	void setRotByOrigin(glm::vec3 angles);

	void rotYaw(float angle);
	void setRotYaw(float angle);

	void rotByOriginPitch(float angle);
	void setRotByOriginPitch(float angle);

	void rotByOrigiYaw(float angle);
	void setRotByOriginYaw(float angle);


	glm::vec3 getPos();
	glm::vec3 getOrigin();
	glm::vec3 getSize();



	void draw();
	void drawHitbox();

};

