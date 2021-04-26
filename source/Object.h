#pragma once
#include "Camera.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texcoord;

public:
	Vertex()
	{
		this->position = glm::vec3(0,0,0);
		this->color = glm::vec3(0,0,0);
		this->texcoord = glm::vec3(0,0,0);
	}
	Vertex(glm::vec3 pos, glm::vec3 color, glm::vec2 tex)
	{
		this->position = pos;
		this->color = color;
		this->texcoord = tex;
	}
	bool operator==(Vertex vertex)
	{
		if (this->position == vertex.position)
			if (this->color == vertex.color)
				return true;
		return false;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Vertex vertex);
};



class Object
{
private:
	Vertex* vertices;
	unsigned int* indices;
	int vnr;
	unsigned int inr;

	void addIndex(int i);
	void addVertex(Vertex vertex);

public:
	Object();
	void appendVertex(Vertex vertex);
	void appendVertex(int i);
	Vertex* ver();
	unsigned int* ind();
	int vNr();
	unsigned int iNr();
	glm::vec3 pos(int number);
	int ind(int i);

	void outputToFile(std::string path);
};

