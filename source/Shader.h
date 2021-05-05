#pragma once
#include "Base.h"

#define GLEW_BUILD

class Shader
{
private:
	unsigned int id;

	unsigned int loadShader(GLenum shaderType, std::string filePath);
	void linkProgram(unsigned int vertexShader, unsigned int fragmentShader);

public:
	Shader();
	Shader(std::string vertexFile, std::string fragmentFile);
	~Shader();

	void use();
	void unuse();
	
	void setUn1i(const char* name, int i);
	void setUn1f(const char* name, float f);

	void setUni2fv(const char* name, glm::fvec2 vector);
	void setUni3fv(const char* name, glm::fvec3 vector);
	void setUni4fv(const char* name, glm::fvec4 vector);

	void setUni3fm(const char* name, glm::fmat3 matrix);
	void setUni4fm(const char* name, glm::fmat4 matrix);


};