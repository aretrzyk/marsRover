#pragma once
#include "Object.h"
class Map :
    public Object
{
    std::vector<Face> faces;

public:
    Map(OBJLoader loader);

    glm::vec3 checkCollision(glm::vec3 origin, glm::vec3 direction, int type);

};

