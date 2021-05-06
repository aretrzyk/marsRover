#include "OBJLoader.h"

OBJLoader::OBJLoader(std::string path)
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
            this->pos.push_back(vec);
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

            this->posElements.push_back(a); 
            this->posElements.push_back(b);
            this->posElements.push_back(c);
            this->texcoordsElements.push_back(atexcoord);
            this->texcoordsElements.push_back(btexcoord);
            this->texcoordsElements.push_back(ctexcoord);
            this->normalsElements.push_back(anormal);
            this->normalsElements.push_back(bnormal);
            this->normalsElements.push_back(cnormal);
            
        }
        else if (line.substr(0, 3) == "vn ")
        {
            std::istringstream ss(line.substr(2));
            GLfloat a, b, c;
            ss >> a;
            ss >> b;
            ss >> c;
            this->normals.push_back(glm::vec3(a, b, c));
        }
    }

    for (int i = 0; i < this->posElements.size(); i++)
    {
        Vertex temp;
        temp.pos = this->pos[this->posElements[i]];
        if(this->texcoordsElements[i] == -1)
            temp.texcoord = glm::vec2(0.f);
        else
            temp.texcoord = this->texcoords[this->texcoordsElements[i]];
        temp.normal = this->normals[this->normalsElements[i]];
        this->vertices.push_back(temp);
    }

}

std::vector<Vertex>& OBJLoader::getVertices()
{
	return this->vertices;
}
