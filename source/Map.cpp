#include "Map.h"

Map::Map(OBJLoader loader) : Object(loader.getVertices(), loader.getHitboxes())
{
	this->faces = loader.getFaces();
}

glm::vec3 Map::checkCollision(glm::vec3 origin, glm::vec3 direction, int type)
{
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	glm::vec3 position;
	glm::vec3 normal;
	for (int i = 0; i < this->faces.size(); i++)
	{
		if (glm::intersectLineTriangle(
			origin,
			direction,
			this->faces[i].vertex1,
			this->faces[i].vertex2,
			this->faces[i].vertex3,
			position
		))
		{
			//std::cout << position.x << " " << position.y << " " << position.z << std::endl;
			if (position.y >= 0 && position.y <= 1
				&& position.z >= 0 && position.z <= 1
				)
			{
				normal = this->faces[i].normal;
				positions.push_back(position);
				normals.push_back(normal);
			}
		}
			
	}
	for (int i = 0; i < positions.size(); i++)
	{
		if (abs(positions[i].x) < abs(position.x))
		{
			position = positions[i];
			normal = normals[i];
		}
			

	}

	if (position.x < 0)
	{
		if(type == 1)
			return 30.f * normal *(-position.x)* Base::dt;
		if(type == 2)
			return 30.f * glm::vec3(0.f, 1.f, 0.f) * (-position.x) * Base::dt;
	}

	return glm::vec3(0.f);
}
