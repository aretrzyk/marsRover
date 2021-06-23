#include "OBJLoader.h"

void OBJLoader::buildMesh()
{
    std::vector<Vertex> verticesTemp;
    Hitbox hitboxTemp;

    hitboxTemp.xMin = pos[posElements[0]].x;
    hitboxTemp.xMax = pos[posElements[0]].x;

    hitboxTemp.yMin = pos[posElements[0]].y;
    hitboxTemp.yMax = pos[posElements[0]].y;

    hitboxTemp.zMin = pos[posElements[0]].z;
    hitboxTemp.zMax = pos[posElements[0]].z;

    if (firstHitbox)
    {
        this->mainHitbox.xMin = hitboxTemp.xMin;
        this->mainHitbox.xMax = hitboxTemp.xMax;

        this->mainHitbox.yMin = hitboxTemp.yMin;
        this->mainHitbox.yMax = hitboxTemp.yMax;

        this->mainHitbox.zMin = hitboxTemp.zMin;
        this->mainHitbox.zMax = hitboxTemp.zMax;
    }

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

        //hitboxes
        if (hitboxTemp.xMin > pos[posElements[i]].x) hitboxTemp.xMin = pos[posElements[i]].x;
        if (hitboxTemp.xMax < pos[posElements[i]].x) hitboxTemp.xMax = pos[posElements[i]].x;

        if (hitboxTemp.yMin > pos[posElements[i]].y) hitboxTemp.yMin = pos[posElements[i]].y;
        if (hitboxTemp.yMax < pos[posElements[i]].y) hitboxTemp.yMax = pos[posElements[i]].y;

        if (hitboxTemp.zMin > pos[posElements[i]].z) hitboxTemp.zMin = pos[posElements[i]].z;
        if (hitboxTemp.zMax < pos[posElements[i]].z) hitboxTemp.zMax = pos[posElements[i]].z;

    }   

    if (this->mainHitbox.xMin > hitboxTemp.xMin) this->mainHitbox.xMin = hitboxTemp.xMin;
    if (this->mainHitbox.xMax > hitboxTemp.xMax) this->mainHitbox.xMax = hitboxTemp.xMax;

    if (this->mainHitbox.yMin > hitboxTemp.yMin) this->mainHitbox.yMin = hitboxTemp.yMin;
    if (this->mainHitbox.yMax > hitboxTemp.yMax) this->mainHitbox.yMax = hitboxTemp.yMax;

    if (this->mainHitbox.zMin > hitboxTemp.zMin) this->mainHitbox.zMin = hitboxTemp.zMin;
    if (this->mainHitbox.zMax > hitboxTemp.zMax) this->mainHitbox.zMax = hitboxTemp.zMax;

    hitboxTemp.size = glm::vec3(
        hitboxTemp.xMax - hitboxTemp.xMin,
        hitboxTemp.yMax - hitboxTemp.yMin,
        hitboxTemp.zMax - hitboxTemp.zMin
    );
    hitboxTemp.origin = glm::dvec3(
        hitboxTemp.xMax - hitboxTemp.size.x / 2,
        hitboxTemp.yMax - hitboxTemp.size.y / 2,
        hitboxTemp.zMax - hitboxTemp.size.z / 2
        );

    this->vertices.push_back(verticesTemp);
    this->hitboxes.push_back(hitboxTemp);

}

OBJLoader::OBJLoader(std::string path)
{
    std::ifstream file(path);
    if (!file)
    {
        std::cout << "Cannot open " << path << std::endl;
        return;
    }

    bool firstObject = true;

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
            
            this->buildMesh();
            this->posElements.clear();
            this->texcoordsElements.clear();
            this->normalsElements.clear();

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

    this->buildMesh();
    this->pos.shrink_to_fit();
    this->texcoords.shrink_to_fit();
    this->normals.shrink_to_fit();

    

}

std::vector<Vertex>& OBJLoader::getVertices()
{
	return this->vertices[0];
}

Hitbox& OBJLoader::getHitboxes()
{
    return this->hitboxes[0];
}

std::vector<Face> OBJLoader::getFaces()
{

    std::vector<Face> faces;

    for (int i = 0; i < posElements.size(); i+=3)
    {
        Face faceTemp(vertices[0][i].pos, vertices[0][i+1].pos, vertices[0][i+2].pos, normals[normalsElements[i]]);
        faces.push_back(faceTemp);
    }

    return faces;

}

Hitbox& OBJLoader::getMainHitbox()
{
    this->mainHitbox.size = glm::vec3(
        this->mainHitbox.xMax - this->mainHitbox.xMin,
        this->mainHitbox.yMax - this->mainHitbox.yMin,
        this->mainHitbox.zMax - this->mainHitbox.zMin
    );
    this->mainHitbox.origin = glm::vec3(
        this->mainHitbox.xMax - this->mainHitbox.size.x / 2,
        this->mainHitbox.yMax - this->mainHitbox.size.y / 2,
        this->mainHitbox.zMax - this->mainHitbox.size.z / 2
    );
    return this->mainHitbox;
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

Hitbox& OBJLoader::getHitboxes(std::string name)
{
    for (int i = 0; i < this->vertices.size(); i++)
    {
        if (this->names[i] == name)
        {
            return this->hitboxes[i];
        }
    }
    std::cout << "Cannot find: " << name << std::endl;
}
