#include "Object.h"

Object::Object()
{
    this->shader = new Shader("res/shaders/basicVShader.vert", "res/shaders/basicFShader.frag");

    glCreateVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &this->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBindVertexArray(0);

	this->translationVec = glm::vec3(1.0f);
	this->rotationVec = glm::vec3(1.0f);
	this->scaleVec = glm::vec3(1.f);

	this->modelMatrix = glm::mat4(1.f);
}

void Object::move(glm::vec3 vec)
{
	this->modelMatrix = glm::translate(this->modelMatrix, this->translationVec);
}

void Object::rotate(glm::vec3 vec)
{
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotationVec.x), glm::vec3(1.f, 0.f, 0.f));
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotationVec.y), glm::vec3(0.f, 1.f, 0.f));
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotationVec.z), glm::vec3(0.f, 0.f, 1.f));
}

void Object::scale(glm::vec3 vec)
{
	this->modelMatrix = glm::scale(this->modelMatrix, this->scaleVec);
}

void Object::setColor(glm::vec4 color)
{
    this->shader->setUni4fv("color", color);
}

void Object::loadFromFile(std::string path)
{
    std::ifstream file(path);
    if (!file)
    {
        std::cout << "Cannot open " << path << std::endl;
    }

    std::string line;
    while (getline(file, line))
    {
        if (line.substr(0, 2) == "v ")
        {
            std::istringstream ss(line.substr(2));
            glm::vec3 vec; 
            ss >> vec.x; 
            ss >> vec.y; 
            ss >> vec.z;
            vertices.push_back(vec);
        }
        else if (line.substr(0, 2) == "f ")
        {
            std::istringstream ss(line.substr(2));
            GLuint a, b, c;
            ss >> a; 
            ss >> b; 
            ss >> c;
            a--; 
            b--; 
            c--;
            elements.push_back(a); elements.push_back(b); elements.push_back(c);
        }
        /*else if (line.substr(0, 2) == "vn ")
        {
            std::istringstream ss(line.substr(2));
            GLfloat a, b, c;
            ss >> a;
            ss >> b;
            ss >> c;
            this->normals.push_back(glm::vec3(a, b, c));
            this->normals.push_back(glm::vec3(a, b, c));
            this->normals.push_back(glm::vec3(a, b, c));
        }*/
        /* anything else is ignored */
    }

    //this->normals.resize(this->vertices.size());
    for (int i = 0; i < this->elements.size(); i += 3)
    {
        /*GLushort ia = elements[i];
        GLushort ib = elements[i + 1];
        GLushort ic = elements[i + 2];
        glm::vec3 normal = glm::normalize(glm::cross(
            glm::vec3(this->vertices[ib]) - glm::vec3(this->vertices[ia]),
            glm::vec3(this->vertices[ic]) - glm::vec3(this->vertices[ia])));*/

        this->normals.push_back(glm::vec3(1.f));
        this->normals.push_back(glm::vec3(1.f));
        this->normals.push_back(glm::vec3(1.f));

    }

    glBindVertexArray(this->VAO);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (const GLvoid*)(this->vertices.size()/2 * sizeof(glm::vec3)));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (const GLvoid*)(this->vertices.size() * sizeof(glm::vec3)));


    //glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * (this->vertices.size()), this->vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * (this->vertices.size() + this->normals.size()), 0, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, this->vertices.size() * sizeof(glm::vec3), this->vertices.data());
    glBufferSubData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), this->normals.size() * sizeof(glm::vec3), this->normals.data());

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->elements.size(), this->elements.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);

}

void Object::draw(glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix, glm::vec3 cameraPos)
{
    glBindVertexArray(this->VAO);

    this->shader->setUni4fm("ModelMatrix", this->modelMatrix);
    this->shader->setUni4fm("ViewMatrix", ViewMatrix);
    this->shader->setUni4fm("ProjectionMatrix", ProjectionMatrix);
    this->shader->setUni3fv("cameraPos", cameraPos);
    lightPos = glm::vec3(10* sin(glfwGetTime()), 10, cos(glfwGetTime()) * 10);
    this->shader->setUni3fv("lightPos", lightPos);
    this->shader->use();
    glDrawElements(GL_TRIANGLES, this->elements.size(), GL_UNSIGNED_INT, 0);
    this->shader->unuse();

    glBindVertexArray(0);
   
}