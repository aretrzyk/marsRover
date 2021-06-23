#include "CubeColider.h"

CubeColider::CubeColider(Hitbox hitbox)
{
	this->hitbox = hitbox;
	this->faces = new Face[12];

    glm::vec3 hitboxPositions[] = {
        glm::vec3(hitbox.xMin, hitbox.yMin, hitbox.zMin), //0
        glm::vec3(hitbox.xMax, hitbox.yMin, hitbox.zMin), //1
        glm::vec3(hitbox.xMax, hitbox.yMax, hitbox.zMin), //2
        glm::vec3(hitbox.xMin, hitbox.yMax, hitbox.zMin), //3

        glm::vec3(hitbox.xMin, hitbox.yMin, hitbox.zMax), //4
        glm::vec3(hitbox.xMax, hitbox.yMin, hitbox.zMax), //5
        glm::vec3(hitbox.xMax, hitbox.yMax, hitbox.zMax), //6
        glm::vec3(hitbox.xMin, hitbox.yMax, hitbox.zMax), //7
    };

    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,  //front faces
        4, 5, 6, 6, 7, 4, //back faces
        1, 5, 4, 4, 2, 1, // left faces
        0, 4, 7, 7, 3, 0, // right faces
        5, 1, 0, 0 ,4, 5, // down faces
        3, 2, 4, 4, 7, 3 // up faces
    };

    for (int i = 0; i < 36; i+=3)
    {
        glm::vec3 v1 = hitboxPositions[indices[i]];
        glm::vec3 v2 = hitboxPositions[indices[i+1]];
        glm::vec3 v3 = hitboxPositions[indices[i+2]];

        this->faces[i / 3] = Face(v1, v2, v3, glm::triangleNormal(v1, v2, v3));
    }
}

CubeColider::~CubeColider()
{
	delete[] this->faces;
}


