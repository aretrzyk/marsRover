#pragma once
#include "Base.h"

class Camera
{
private:
	//Camera position
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	float cameraSpeed;
	//Camera rotation
	float yaw;
	float pitch;

	//Camera settings
	float fov;
	float nearPlane;
	float farPlane;

	//Mouse pos (for moving camera by mouse)
	double lastPosX;
	double lastPosY;

	//Frame times for calculating delta time
	float currentFrameTime;
	float previousFrameTime;

	//Should prevent camera from jumping when coming into window but...
	bool firstMove;

	//Distance from camera center, its "handle"
	float cameraDistance;
	float cameraHeight;

	void updateMousePos();
	void updateDeltaTime();
	void updateInputs(); // for free cam
	void updateCamera();
	void updateViewMatrix();
	void updateProjectionMatrix();
public:
	Camera();
	void updateFreeCam();
	void updateThirdPersCam(glm::vec3 pos, float yaw, float pitch);
};
