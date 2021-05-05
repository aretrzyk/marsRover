#pragma once
#include "Shader.h"

class Camera
{
private:
	glm::vec3 cameraPosition;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	float cameraSpeed;

	float fov;
	float nearPlane;
	float farPlane;

	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

	float yaw;
	float pitch;

	double lastPosX;
	double lastPosY;

	float dt;
	float currentFrameTime;
	float previousFrameTime;


	bool firstMove;

	GLFWwindow* windowPtr;

	void updatePos();
	void updateDeltaTime();
	void updateInputs();
	void updateCamera();
	void updateViewMatrix();
	void updateProjectionMatrix();
public:
	Camera(GLFWwindow* window);
	void update();

	glm::mat4 projectionMatrix();
	glm::mat4 viewMatrix();

	glm::vec3 pos();
	
};
