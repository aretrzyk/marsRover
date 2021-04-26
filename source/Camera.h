#pragma once
#include "Shader.h"

class Camera
{
private:
	glm::vec3 cameraPosition;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	float cameraSpeed = 3;

	float fov = 45.f;
	float nearPlane = 0.1f;
	float farPlane = 100.f;

	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

	float yaw = 0;
	float pitch = 0;

	double lastPosX;
	double lastPosY;

	float dt;
	float currentFrameTime;
	float previousFrameTime;


	bool firstMove = true;

	GLFWwindow* windowPtr;

	void updatePos();
	void updateDeltaTime();
	void updateInputs();
	void updateCamera();
	void updateViewMatrix();
	void updateProjectionMatrix();
public:
	Camera(GLFWwindow* window);
	void update(Shader* program);
	
};
