#pragma once
#include "Vertex.h"

class OBJLoader
{
private:
	std::vector<std::vector<Vertex>> vertices;
	std::vector<std::string> names;

	

public:
	OBJLoader(std::string path);
	//one object
	std::vector<Vertex>& getVertices();
	//when you have kilka objects in file
	std::vector<Vertex>& getVertices(std::string name);
	
};
