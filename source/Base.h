#pragma once
#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>
#include <GLM/vec4.hpp>
#include <GLM/mat4x4.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/gtc/constants.hpp>
#include <GLM/gtx/intersect.hpp>
#include <GLM/gtx/normal.hpp >
#include <GLM/gtx/vector_angle.hpp >


class Base
{
public:
	//Window
	static GLFWwindow* window;

	//Lighting
	static glm::vec3 lightPos;
	static glm::vec3 lightColor;
	//Camera
	static glm::vec3 cameraPos;
	//View
	static glm::mat4 viewMatrix;
	static glm::mat4 projectionMatrix;
	//Delta time
	static float dt;
};

