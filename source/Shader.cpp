#include "Shader.h"


unsigned int Shader::loadShader(GLenum shaderType, std::string filePath)
{
	std::ifstream shaderSource(filePath);

	std::string shaderString;
	std::string line;

	while (getline(shaderSource, line))
	{
		shaderString.append(line);
		shaderString.append("\n");
	}
	shaderSource.close();
	unsigned int shader = glCreateShader(shaderType);
	const char* src = shaderString.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	int error;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &error);
	if (error == GL_FALSE)
	{
		int errorLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLength);
		char* errorMessage = (char*)alloca(errorLength * sizeof(char));
		glGetShaderInfoLog(shader, errorLength, &errorLength, errorMessage);
		std::cout << errorMessage << std::endl;
	}
	return shader;
}

void Shader::linkProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	glAttachShader(this->id, vertexShader);
	glAttachShader(this->id, fragmentShader);
	glLinkProgram(this->id);
	glValidateProgram(this->id);
	int error;
	glGetProgramiv(this->id, GL_LINK_STATUS, &error);
	if (error == GL_FALSE)
	{
		int errorLength;
		glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &errorLength);
		char* errorMessage = (char*)alloca(errorLength * sizeof(char));
		glGetProgramInfoLog(this->id, errorLength, &errorLength, errorMessage);
		std::cout << errorMessage << std::endl;
	}
	//marking shaders for delete 
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::Shader()
{
	this->id = glCreateProgram();
	unsigned int vs = this->loadShader(GL_VERTEX_SHADER, "res/shaders/basicVShader.vert");
	unsigned int fs = this->loadShader(GL_FRAGMENT_SHADER,"res/shaders/basicFShader.frag");
	this->linkProgram(vs, fs);
}

Shader::Shader(std::string vertexFile, std::string fragmentFile)
{
	this->id = glCreateProgram();
	unsigned int vs = this->loadShader(GL_VERTEX_SHADER, vertexFile);
	unsigned int fs = this->loadShader(GL_FRAGMENT_SHADER, fragmentFile);
	this->linkProgram(vs, fs);
}

Shader::~Shader()
{
    glDeleteProgram(this->id);
}

void Shader::use()
{
	glUseProgram(this->id);
}

void Shader::unuse()
{
	glUseProgram(0);
}

void Shader::setUn1i(const char* name, int i)
{
	glUseProgram(this->id);
	glUniform1i(glGetUniformLocation(this->id, name), i);
	glUseProgram(0);
}

void Shader::setUn1f(const char* name, float f)
{
	glUseProgram(this->id);
	glUniform1f(glGetUniformLocation(this->id, name), f);
	glUseProgram(0);
}

void Shader::setUni2fv(const char* name, glm::fvec2 vector)
{
	glUseProgram(this->id);
	glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(vector));
	glUseProgram(0);
}

void Shader::setUni3fv(const char* name, glm::fvec3 vector)
{
	glUseProgram(this->id);
	glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(vector));
	glUseProgram(0);
}

void Shader::setUni4fv(const char* name, glm::fvec4 vector)
{
	glUseProgram(this->id);
	glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(vector));
	glUseProgram(0);
}

void Shader::setUni3fm(const char* name, glm::fmat3 matrix)
{
	glUseProgram(this->id);
	glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(matrix));
	glUseProgram(0);
}

void Shader::setUni4fm(const char* name, glm::fmat4 matrix)
{
	glUseProgram(this->id);
	glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(matrix));
	glUseProgram(0);
}
