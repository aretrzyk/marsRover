#include "Camera.h"

void Camera::updateMousePos()
{
	//Zczytywanie aktualnej pozycji kursora
	double currPosX;
	double currPosY;
	glfwGetCursorPos(Base::window, &currPosX, &currPosY);
	//std::cout << currPosX << "," << currPosY << std::endl;
	//Zabezpieczenie przezd nag³ym skokiem kamery gry pierwszy raz ni¹ ruszamy
	//Pasowa³by zrobic ¿e kamera startuje skierowana na œrodek a nie trzeba ruszac i szukaæ œrodka i obiektu
	if (this->firstMove)
	{
		this->lastPosX = currPosX;
		this->lastPosX = currPosY;
		this->firstMove = false;
	}
	//Obliczenie jaki ruch wykona³a myszka
	float mouseOffsetX = currPosX - this->lastPosX;
	float mouseOffsetY = currPosY - this->lastPosY;
	this->lastPosX = currPosX;
	this->lastPosY = currPosY;

	//Uwzglêdnienie czu³oœci
	const float sensitivity = 0.1f;
	mouseOffsetX *= sensitivity;
	mouseOffsetY *= sensitivity;

	//Nowe k¹ty obrotu dla kamery
	this->yaw += mouseOffsetX;
	this->pitch += mouseOffsetY;
}

void Camera::updateDeltaTime()
{
	this->previousFrameTime = this->currentFrameTime;
	this->currentFrameTime = glfwGetTime();
	Base::dt = this->currentFrameTime - this->previousFrameTime;
}

void Camera::updateInputs()
{
	if (glfwGetKey(Base::window, GLFW_KEY_W) == GLFW_PRESS)
		Base::cameraPos += glm::normalize(this->cameraFront) * this->cameraSpeed * Base::dt;
	if (glfwGetKey(Base::window, GLFW_KEY_S) == GLFW_PRESS)
		Base::cameraPos -= glm::normalize(this->cameraFront) * this->cameraSpeed * Base::dt;
	if (glfwGetKey(Base::window, GLFW_KEY_SPACE) == GLFW_PRESS)
		Base::cameraPos += glm::normalize(this->cameraUp) * this->cameraSpeed * Base::dt;
	if (glfwGetKey(Base::window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		Base::cameraPos -= glm::normalize(this->cameraUp) * this->cameraSpeed * Base::dt;
	if (glfwGetKey(Base::window, GLFW_KEY_D) == GLFW_PRESS)
		Base::cameraPos += this->cameraSpeed * glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * Base::dt;
	if (glfwGetKey(Base::window, GLFW_KEY_A) == GLFW_PRESS)
		Base::cameraPos -= this->cameraSpeed * glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * Base::dt;
}

void Camera::updateCamera()
{
	//Blokada przed z³amaniem sobie karku
	if (pitch > 89.0f)
		pitch = 89.f;
	if (pitch < -89.f)
		pitch = -89.f;

	glm::vec3 cameraDirection;
	cameraDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraDirection.y = -sin(glm::radians(pitch));
	cameraDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->cameraFront = glm::normalize(cameraDirection);
}

void Camera::updateViewMatrix()
{
	Base::viewMatrix = glm::lookAt(Base::cameraPos, Base::cameraPos + cameraFront, cameraUp);
}

void Camera::updateProjectionMatrix()
{
	int framebufferWidth, framebufferHeight;
	glfwGetFramebufferSize(Base::window, &framebufferWidth, &framebufferHeight);

	Base::projectionMatrix = glm::perspective
	(
		glm::radians(fov),
		(float)framebufferWidth / (float)framebufferHeight,
		nearPlane,
		farPlane
	);
}

Camera::Camera()
{
	this->cameraFront = glm::vec3(0.f, 0.f, -1.f);
	this->cameraUp = glm::vec3(0.f, 1.f, 0.f);
	this->cameraSpeed = 5.f;
	
	this->fov = 90.f;
	this->nearPlane = 0.1f;
	this->farPlane = 1000.f;

	this->yaw = 0;
	this->pitch = 0;

	this->lastPosX = 0;
	this->lastPosY = 0;

	this->currentFrameTime = glfwGetTime();
	this->previousFrameTime = this->currentFrameTime;

	this->firstMove = true;

	this->cameraDistance = -12;
	this->cameraHeight = 8;
}

void Camera::updateFreeCam()
{
	this->updateMousePos();
	this->updateDeltaTime();
	this->updateInputs();
	this->updateCamera();
	this->updateViewMatrix();
	this->updateProjectionMatrix();
}

void Camera::updateThirdPersCam(glm::vec3 pos, float yaw, float pitch)
{
	//Base::cameraPos = pos;
	this->yaw = yaw;
	this->pitch = pitch;
	float z = this->cameraDistance * sin(glm::radians(yaw)) + pos.z;
	float x = this->cameraDistance * cos(glm::radians(yaw)) + pos.x;
	float y = pos.y + this->cameraHeight;
	Base::cameraPos = glm::vec3(x, y, z);

	this->updateDeltaTime();
	this->updateCamera();
	this->updateViewMatrix();
	this->updateProjectionMatrix();

}


