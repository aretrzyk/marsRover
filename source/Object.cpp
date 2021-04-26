#include "Object.h"

std::ostream& operator<<(std::ostream& stream, const Vertex vertex)
{
	stream << vertex.position.x << "," << vertex.position.y << "," << vertex.position.z << " " << vertex.color.x << "," << vertex.color.y << "," << vertex.color.z;
	return stream;
}


void Object::addIndex(int i)
{
	unsigned int* temp = new unsigned int[inr + 1];
	memcpy(temp, this->indices, sizeof(int) * this->inr);
	temp[inr] = i;
	delete[] this->indices;
	this->indices = temp;
	inr++;
}

void Object::addVertex(Vertex vertex)
{
	Vertex* temp = new Vertex[vnr + 1];
	memcpy(temp, this->vertices, sizeof(Vertex) * this->vnr);
	temp[vnr] = vertex;
	delete[] this->vertices;
	this->vertices = temp;
	vnr++;
}

Object::Object()
{
	this->vnr = 0;
	this->inr = 0;
	this->vertices = new Vertex[vnr];
	this->indices = new unsigned int[inr];
}

void Object::appendVertex(Vertex vertex)
{
	for (int i = 0; i < this->vnr; i++)
	{
		if (this->vertices[i] == vertex)
		{
			this->addIndex(i);
			return;
		}
	}
	this->addIndex(this->vnr);
	this->addVertex(vertex);
}

void Object::appendVertex(int i)
{
	this->addIndex(i);
}

Vertex* Object::ver()
{
	return this->vertices;
}

unsigned int* Object::ind()
{
	return this->indices;
}

int Object::vNr()
{
	return this->vnr;
}

unsigned int Object::iNr()
{
	return this->inr;
}

glm::vec3 Object::pos(int number)
{
	return vertices[number].position;
}

int Object::ind(int i)
{
	return this->indices[i];
}

void Object::outputToFile(std::string path)
{
	unsigned i;
	std::ofstream file(path);
	for (i = 0; i < this->vnr; i++)
	{
		file << this->vertices[i] << std::endl;
	}
	for (i = 0; i < this->inr; i++)
	{
		file << this->indices[i] << std::endl;
	}
}
