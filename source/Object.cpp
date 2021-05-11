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
        glm::vec3(hitbox.xMin, hitbox.yMax, hitbox.zMax)  //7
    };

    unsigned int indices[] = { 
        0, 1, 1, 2, 2, 3, 3, 0, //front face
        4, 5, 5, 6, 6, 7, 7, 4, //back face
        0, 4, 1, 5, 2, 6, 3, 7, 0, 4 // links between faces
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
    this->modelMatrix = glm::translate(this->modelMatrix, this->posVec);
    this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotationVec.x), glm::vec3(1.f, 0.f, 0.f));
    this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotationVec.y), glm::vec3(0.f, 1.f, 0.f));
    this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotationVec.z), glm::vec3(0.f, 0.f, 1.f));
    this->modelMatrix = glm::scale(this->modelMatrix, this->scaleVec);
}

Object::Object()
{
    this->shader = new Shader("res/shaders/basicVShader.vert", "res/shaders/basicFShader.frag");

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
	this->rotationVec = glm::vec3(0.0f);
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
}


void Object::move(glm::vec3 vec)
{
    this->posVec = vec;
}

void Object::rotate(glm::vec3 vec)
{
    this->rotationVec += vec;
}

void Object::scale(glm::vec3 vec)
{
    this->scaleVec = vec;
}

void Object::setColor(glm::vec3 color)
{
    this->objectColor = glm::vec4(color, 1.f);
}

void Object::setColor(glm::vec4 color)
{
    this->objectColor = color;
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
    this->shader->setUni4fm("ModelMatrix", this->modelMatrix);
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

    this->shader->setUni4fv("color", this->hitboxColor);
    this->shader->setUni4fm("ModelMatrix", this->modelMatrix);
    this->shader->setUni4fm("ViewMatrix", Base::viewMatrix);
    this->shader->setUni4fm("ProjectionMatrix", Base::projectionMatrix);
    this->shader->setUni3fv("cameraPos", Base::cameraPos);
    this->shader->setUni3fv("lightPos", Base::lightPos);
    this->shader->setUni3fv("lightColor", Base::lightColor);

    this->shader->use();
    glDrawArrays(GL_LINES, 0, this->hitboxIndicesNumber);
    this->shader->unuse();

    glBindVertexArray(0);
}
