#include "Object.h"

void Object::loadHitbox()
{
    glm::vec3 hitboxPositions[] = {
        glm::vec3(hitbox.xMin, hitbox.yMin, hitbox.zMin), //0
        glm::vec3(hitbox.xMax, hitbox.yMin, hitbox.zMin), //1
        glm::vec3(hitbox.xMax, hitbox.yMax, hitbox.zMin), //2
        glm::vec3(hitbox.xMin, hitbox.yMax, hitbox.zMin), //3

        glm::vec3(hitbox.xMin, hitbox.yMin, hitbox.zMax), //4
        glm::vec3(hitbox.xMax, hitbox.yMin, hitbox.zMax), //5
        glm::vec3(hitbox.xMax, hitbox.yMax, hitbox.zMax), //6
        glm::vec3(hitbox.xMin, hitbox.yMax, hitbox.zMax), //7

        glm::vec3(hitbox.xMin + hitbox.size.x / 2, hitbox.yMin, hitbox.zMin + hitbox.size.z / 2), //8
        glm::vec3(hitbox.xMin + hitbox.size.x / 2, hitbox.yMax, hitbox.zMin + hitbox.size.z / 2), //9

        glm::vec3(hitbox.xMin, hitbox.yMin + hitbox.size.y / 2, hitbox.zMin + hitbox.size.z / 2), //10
        glm::vec3(hitbox.xMax, hitbox.yMin + hitbox.size.y / 2, hitbox.zMin + hitbox.size.z / 2), //11

        glm::vec3(hitbox.xMin + hitbox.size.x / 2, hitbox.yMin + hitbox.size.y / 2, hitbox.zMin), //12
        glm::vec3(hitbox.xMin + hitbox.size.x / 2, hitbox.yMin + hitbox.size.y / 2, hitbox.zMax), //13

        //glm::vec3(0,0,0), //14
        //hitbox.origin, //15
        
    };
    unsigned int indices[] = { 
        0, 1, 1, 2, 2, 3, 3, 0, //front face
        4, 5, 5, 6, 6, 7, 7, 4, //back face
        0, 4, 1, 5, 2, 6, 3, 7, 0, 4, // links between faces
        8, 9, 10, 11, 12, 13 //centre
        //,14, 15 //posVec
    };
    this->hitboxIndicesNumber = sizeof(indices) / sizeof(indices[0]);

    glBindVertexArray(this->VAO);
    glGenBuffers(1, &this->hitboxVBO);

    std::vector<glm::vec3> hitboxVertices;
    for (int i = 0; i < this->hitboxIndicesNumber; i++)
        hitboxVertices.push_back(hitboxPositions[indices[i]]);
    hitboxVertices.shrink_to_fit();

    glBindBuffer(GL_ARRAY_BUFFER, this->hitboxVBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
    glBufferData(GL_ARRAY_BUFFER, this->hitboxIndicesNumber * sizeof(glm::vec3), hitboxVertices.data(), GL_DYNAMIC_DRAW);

    glBindVertexArray(0);
    
}

void Object::updateModelMatrix()
{
    this->modelMatrix = glm::mat4(1.f);
    this->rotByOriginMatrix = glm::mat4(1.f);

    

    this->modelMatrix = glm::translate(this->modelMatrix, this->posVec);

    this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotVec.y), glm::vec3(0.f, 1.f, 0.f));
    this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotVec.z), glm::vec3(0.f, 0.f, 1.f));
    this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotVec.x), glm::vec3(1.f, 0.f, 0.f));
    

    this->rotByOriginMatrix = glm::translate(this->rotByOriginMatrix, this->hitbox.getOrigin());
    this->rotByOriginMatrix = glm::rotate(this->rotByOriginMatrix, glm::radians(this->rotByOriginVec.z), glm::vec3(0.f, 0.f, 1.f));
    this->rotByOriginMatrix = glm::rotate(this->rotByOriginMatrix, glm::radians(this->rotByOriginVec.y), glm::vec3(0.f, 1.f, 0.f));
    this->rotByOriginMatrix = glm::rotate(this->rotByOriginMatrix, glm::radians(this->rotByOriginVec.x), glm::vec3(1.f, 0.f, 0.f));
    this->rotByOriginMatrix = glm::translate(this->rotByOriginMatrix, -this->hitbox.getOrigin());

    this->modelMatrix = glm::scale(this->modelMatrix, this->scaleVec);

}

Object::Object()
{
    this->shader = new Shader("res/shaders/basicVShader.vert", "res/shaders/basicFShader.frag");
    this->shaderHitbox = new Shader("res/shaders/basicVShader.vert", "res/shaders/basicFShader.frag");

    glCreateVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    this->objectColor = glm::vec4(1, 0.5, 0.5, 1);
    this->hitboxColor = glm::vec4(1, 1, 1, 1);

	this->posVec = glm::vec3(0.0f);
	this->rotVec = glm::vec3(0.0f);
	this->rotByOriginVec = glm::vec3(0.0f);
	this->scaleVec = glm::vec3(1.f);

	this->modelMatrix = glm::mat4(1.f);

}


Object::Object(std::vector<Vertex> vertices, Hitbox hitbox) : Object()
{
    this->load(vertices);
    this->hitbox = hitbox;
    this->loadHitbox();
}

Object::~Object()
{
    delete this->shader;
    delete this->shaderHitbox;
}


void Object::setColor(glm::vec3 color)
{
    this->objectColor = glm::vec4(color, 1.f);
}

void Object::setColor(glm::vec4 color)
{
    this->objectColor = color;
}

void Object::setSize(glm::vec3 size)
{
    this->scaleVec = size;
}

void Object::move(glm::vec3 vec)
{
    this->posVec += vec;
}

void Object::setPos(glm::vec3 vec)
{
    this->posVec = vec;
}

void Object::setY(float y)
{
    this->posVec.y = y;
}

void Object::rot(glm::vec3 angles)
{
    this->rotVec += angles;
}

void Object::setRot(glm::vec3 angles)
{
    this->rotVec = angles;
}

void Object::rotByOrigin(glm::vec3 angles)
{
    this->rotByOriginVec += angles;
}

void Object::setRotByOrigin(glm::vec3 angles)
{
    this->rotByOriginVec = angles;
}

void Object::rotYaw(float angle)
{
    this->rotVec.y += angle;
}

void Object::setRotYaw(float angle)
{
    this->rotVec.y = angle;
}

void Object::rotPitch(float angle)
{
    this->rotVec.x += angle;
}

void Object::setRotPitch(float angle)
{
    this->rotVec.x = angle;
}

void Object::rotRoll(float angle)
{
    this->rotVec.z += angle;
}

void Object::setRotRoll(float angle)
{
    this->rotVec.z = angle;
}

void Object::rotByOriginPitch(float angle)
{
    this->rotByOriginVec.x += angle;
}

void Object::setRotByOriginPitch(float angle)
{
    this->rotByOriginVec.x = angle;
}

void Object::rotByOrigiYaw(float angle)
{
    this->rotByOriginVec.y += angle;
}

void Object::setRotByOriginYaw(float angle)
{
    this->rotByOriginVec.y = angle;
}

glm::vec3 Object::getPos()
{
    this->updateModelMatrix();
    return glm::vec3(this->modelMatrix * glm::vec4(0,0,0,1));
}

glm::vec3 Object::getOrigin()
{
    this->updateModelMatrix();
    return glm::vec3(this->modelMatrix * glm::vec4(this->hitbox.getOrigin(), 1.f));
}

glm::vec3 Object::getSize()
{
    return this->hitbox.getSize();
}

void Object::load(std::vector<Vertex> vertices)
{
    this->verticesCount = vertices.size();

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);

    glBindVertexArray(0);

}


void Object::draw()
{
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));

    this->updateModelMatrix();
    this->shader->setUni4fv("color", this->objectColor);
    this->shader->setUni4fm("ModelMatrix", this->modelMatrix * this->rotByOriginMatrix);
    this->shader->setUni4fm("ViewMatrix", Base::viewMatrix);
    this->shader->setUni4fm("ProjectionMatrix", Base::projectionMatrix);
    this->shader->setUni3fv("cameraPos", Base::cameraPos);
    this->shader->setUni3fv("lightPos", Base::lightPos);
    this->shader->setUni3fv("lightColor", Base::lightColor);
    this->shader->use();
    glDrawArrays(GL_TRIANGLES, 0, this->verticesCount);
    this->shader->unuse();

    glBindVertexArray(0);
}

void Object::drawHitbox()
{
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->hitboxVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

    this->shaderHitbox->setUni4fv("color", this->hitboxColor);
    this->shaderHitbox->setUni4fm("ModelMatrix", glm::mat4(1.f));
    this->shaderHitbox->setUni4fm("ViewMatrix", Base::viewMatrix);
    this->shaderHitbox->setUni4fm("ProjectionMatrix", Base::projectionMatrix);
    this->shaderHitbox->setUni3fv("cameraPos", Base::cameraPos);
    this->shaderHitbox->setUni3fv("lightPos", Base::lightPos);
    this->shaderHitbox->setUni3fv("lightColor", Base::lightColor);

    this->shaderHitbox->use();
    glDrawArrays(GL_LINES, 0, this->hitboxIndicesNumber);
    this->shaderHitbox->unuse();

    glBindVertexArray(0);
}
