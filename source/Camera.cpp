#include "Camera.h"

void Camera::updatePos()
{
	double currPosX;
	double currPosY;
	glfwGetCursorPos(this->windowPtr, &currPosX, &currPosY);

	if (this->firstMove)
	{
		lastPosX = currPosX;
		lastPosX = currPosY;
		firstMove = false;
	}
	float mouseOffsetX = currPosX - lastPosX;
	float mouseOffsetY = currPosY - lastPosY;
	lastPosX = currPosX;
	lastPosY = currPosY;

	const float sensitivity = 0.1f;
	mouseOffsetX *= sensitivity;
	mouseOffsetY *= sensitivity;

	yaw += mouseOffsetX;
	pitch += mouseOffsetY;
}

void Camera::updateDeltaTime()
{
	this->previousFrameTime = this->currentFrameTime;
	this->currentFrameTime = glfwGetTime();
	this->dt = this->currentFrameTime - this->previousFrameTime;
}

void Camera::updateInputs()
{
	if (glfwGetKey(this->windowPtr, GLFW_KEY_W) == GLFW_PRESS)
		this->cameraPosition += glm::normalize(this->cameraFront) * this->cameraSpeed * this->dt;
	if (glfwGetKey(this->windowPtr, GLFW_KEY_S) == GLFW_PRESS)
		this->cameraPosition -= glm::normalize(this->cameraFront) * this->cameraSpeed * this->dt;
	if (glfwGetKey(this->windowPtr, GLFW_KEY_SPACE) == GLFW_PRESS)
		this->cameraPosition += glm::normalize(this->cameraUp) * this->cameraSpeed * this->dt;
	if (glfwGetKey(this->windowPtr, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		this->cameraPosition -= glm::normalize(this->cameraUp) * this->cameraSpeed * this->dt;
	if (glfwGetKey(this->windowPtr, GLFW_KEY_D) == GLFW_PRESS)
		this->cameraPosition += this->cameraSpeed * glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * this->dt;
	if (glfwGetKey(this->windowPtr, GLFW_KEY_A) == GLFW_PRESS)
		this->cameraPosition -= this->cameraSpeed * glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * this->dt;
}

void Camera::updateCamera()
{
	if (this->pitch > 89.0f)
		this->pitch = 89.f;
	if (this->pitch < -89.f)
		this->pitch = -89.f;
	glm::vec3 cameraDirection;
	cameraDirection.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	cameraDirection.y = -sin(glm::radians(this->pitch));
	cameraDirection.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->cameraFront = glm::normalize(cameraDirection);
}

void Camera::updateViewMatrix()
{
	this->ViewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
}

void Camera::updateProjectionMatrix()
{
	int framebufferWidth, framebufferHeight;
	glfwGetFramebufferSize(this->windowPtr, &framebufferWidth, &framebufferHeight);

	this->ProjectionMatrix = glm::perspective
	(
		glm::radians(fov),
		(float)framebufferWidth / (float)framebufferHeight,
		nearPlane,
		farPlane
	);
}

Camera::Camera(GLFWwindow* window)
{
	this->windowPtr = window;

	this->cameraPosition = glm::vec3(0.0f, 0.0f, 10.0f);
	this->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	this->ViewMatrix = glm::mat4(1.0f);
	this->ProjectionMatrix = glm::mat4(1.0f);
	
	this->currentFrameTime = glfwGetTime();
	this->previousFrameTime = this->currentFrameTime;
}

void Camera::update(Shader* program)
{
	this->updatePos();
	this->updateDeltaTime();
	this->updateInputs();
	this->updateCamera();
	this->updateViewMatrix();
	this->updateProjectionMatrix();
	program->setUni4fm("ViewMatrix", this->ViewMatrix);
	program->setUni4fm("ProjectionMatrix", this->ProjectionMatrix);
}


