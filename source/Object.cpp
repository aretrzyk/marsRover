#include "Object.h"

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

    //glGenBuffers(1, &this->EBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBindVertexArray(0);

	this->posVec = glm::vec3(0.0f);
	this->rotationVec = glm::vec3(0.0f);
	this->scaleVec = glm::vec3(1.f);

	this->modelMatrix = glm::mat4(1.f);
}

void Object::move(glm::vec3 vec)
{
    glm::vec3 moveVec = vec - this->posVec;
    this->posVec = vec;
}

void Object::rotate(glm::vec3 vec)
{
    this->modelMatrix = glm::mat4(1.f);
    this->rotationVec += vec;
}

void Object::scale(glm::vec3 vec)
{
    this->scaleVec = vec;
}

void Object::setColor(glm::vec3 color)
{
    this->shader->setUni4fv("color", glm::vec4(color, 1.f));
}

void Object::setColor(glm::vec4 color)
{
    this->shader->setUni4fv("color", color);
}

void Object::load(std::vector<Vertex>& vertices)
{
    this->verticesCount = vertices.size();

    glBindVertexArray(this->VAO);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);

}

void Object::draw()
{
    glBindVertexArray(this->VAO);

    this->updateModelMatrix();
    this->shader->setUni4fm("ModelMatrix", this->modelMatrix);
    this->shader->setUni4fm("ViewMatrix", Base::viewMatrix);
    this->shader->setUni4fm("ProjectionMatrix", Base::projectionMatrix);
    this->shader->setUni3fv("cameraPos", Base::cameraPos);
    this->shader->setUni3fv("lightPos", Base::lightPos);
    this->shader->setUni3fv("lightColor", Base::lightColor);
    this->shader->use();
    glDrawArrays(GL_TRIANGLES, 0, this->verticesCount);
    //glDrawElements(GL_TRIANGLES, this->elements.size(), GL_UNSIGNED_INT, 0);
    this->shader->unuse();

    glBindVertexArray(0);
   
}