#include "OBJLoader.h"

OBJLoader::OBJLoader(std::string path)
{
    std::ifstream file(path);
    if (!file)
    {
        std::cout << "Cannot open " << path << std::endl;
    }

    bool firstObject = true;

    std::vector<glm::vec3> pos;
    std::vector<glm::vec2> texcoords;
    std::vector<glm::vec3> normals;

    std::vector<GLuint> posElements;
    std::vector<GLint> texcoordsElements;
    std::vector<GLuint> normalsElements;

    std::string line;
    while (getline(file, line))
    {
        if (line.substr(0, 2) == "o ")
        {
            if (firstObject)
            {
                std::istringstream ss(line.substr(2));
                std::string objectName;
                ss >> objectName;
                this->names.push_back(objectName);
                firstObject = false;
                continue;
            }

            std::vector<Vertex> verticesTemp;
            for (int i = 0; i < posElements.size(); i++)
            {
                Vertex temp;
                temp.pos = pos[posElements[i]];
                if (texcoordsElements[i] == -1)
                    temp.texcoord = glm::vec2(0.f);
                else
                    temp.texcoord = texcoords[texcoordsElements[i]];
                temp.normal = normals[normalsElements[i]];
                verticesTemp.push_back(temp);
            }

            this->vertices.push_back(verticesTemp);

            //pos.clear();
            //texcoords.clear();
            //normals.clear();

            posElements.clear();
            texcoordsElements.clear();
            normalsElements.clear();

            std::istringstream ss(line.substr(2));
            std::string objectName;
            ss >> objectName;
            this->names.push_back(objectName);

        }
        else if (line.substr(0, 2) == "v ")
        {
            std::istringstream ss(line.substr(2));
            glm::vec3 vec;
            ss >> vec.x;
            ss >> vec.y;
            ss >> vec.z;
            
            pos.push_back(vec);
        }
        else if (line.substr(0, 2) == "f ")
        {
            std::istringstream ss(line.substr(2));
            GLuint a, b, c;
            GLint atexcoord, btexcoord, ctexcoord;
            GLuint anormal, bnormal, cnormal;
            GLuint temp;
            
            ss >> a;
            if (ss.peek() == '/')
            {
                ss.ignore(1, '/');

                if (ss.peek() == '/')
                {
                    ss.ignore(1, '/');
                    ss >> anormal;
                    atexcoord = 0;
                }
                else
                {
                    ss >> atexcoord;
                    ss.ignore(1, '/');
                    ss >> anormal;
                }
                
            }
            ss.ignore(1, ' ');

            ss >> b;
            if (ss.peek() == '/')
            {
                ss.ignore(1, '/');

                if (ss.peek() == '/')
                {
                    ss.ignore(1, '/');
                    ss >> bnormal;
                    btexcoord = 0;
                }
                else
                {
                    ss >> btexcoord;
                    ss.ignore(1, '/');
                    ss >> bnormal;
                }

            }
            ss.ignore(1, ' ');

            ss >> c;
            if (ss.peek() == '/')
            {
                ss.ignore(1, '/');

                if (ss.peek() == '/')
                {
                    ss.ignore(1, '/');
                    ss >> cnormal;
                    ctexcoord = 0;
                }
                else
                {
                    ss >> ctexcoord;
                    ss.ignore(1, '/');
                    ss >> cnormal;
                }

            }
            ss.ignore(1, ' ');
            a--; b--; c--;
            atexcoord--; btexcoord--; ctexcoord--;
            anormal--; bnormal--; cnormal--;

            posElements.push_back(a); 
            posElements.push_back(b);
            posElements.push_back(c);
            texcoordsElements.push_back(atexcoord);
            texcoordsElements.push_back(btexcoord);
            texcoordsElements.push_back(ctexcoord);
            normalsElements.push_back(anormal);
            normalsElements.push_back(bnormal);
            normalsElements.push_back(cnormal);
            
        }
        else if (line.substr(0, 3) == "vn ")
        {
            std::istringstream ss(line.substr(2));
            GLfloat a, b, c;
            ss >> a;
            ss >> b;
            ss >> c;
            normals.push_back(glm::vec3(a, b, c));
        }
        else if (line.substr(0, 3) == "vt ")
        {
        std::istringstream ss(line.substr(2));
        GLfloat a, b;
        ss >> a;
        ss >> b;
        texcoords.push_back(glm::vec2(a, b));
        }

    }

    std::vector<Vertex> verticesTemp;
    for (int i = 0; i < posElements.size(); i++)
    {
        Vertex temp;
        temp.pos = pos[posElements[i]];
        if (texcoordsElements[i] == -1)
            temp.texcoord = glm::vec2(0.f);
        else
            temp.texcoord = texcoords[texcoordsElements[i]];
        temp.normal = normals[normalsElements[i]];
        verticesTemp.push_back(temp);
    }

    this->vertices.push_back(verticesTemp);
}

std::vector<Vertex>& OBJLoader::getVertices()
{
	return this->vertices[0];
}

std::vector<Vertex>& OBJLoader::getVertices(std::string name)
{
    for (int i = 0; i < this->vertices.size(); i++)
    {
        if (this->names[i] == name)
        {
            return this->vertices[i];
        }
    }
    std::cout << "Cannot find: " << name << std::endl;
}
