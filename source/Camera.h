#pragma once
#include "Base.h"

class Camera
{
private:
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	float cameraSpeed;

	float fov;
	float nearPlane;
	float farPlane;

	float yaw;
	float pitch;

	double lastPosX;
	double lastPosY;

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
};
