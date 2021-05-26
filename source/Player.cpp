#include "Player.h"
#include <ios>

void Player::initObjects(OBJLoader& loader)
{
	this->head = new Object(loader.getVertices("head"), loader.getHitboxes("head"));
	this->body = new Object(loader.getVertices("body"), loader.getHitboxes("body"));
	this->frontLeftWheel = new Object(loader.getVertices("frontLeftWheel"), loader.getHitboxes("frontLeftWheel"));
	this->frontRightWheel = new Object(loader.getVertices("frontRightWheel"), loader.getHitboxes("frontRightWheel"));
	this->middleLeftWheel = new Object(loader.getVertices("middleLeftWheel"), loader.getHitboxes("middleLeftWheel"));
	this->middleRightWheel = new Object(loader.getVertices("middleRightWheel"), loader.getHitboxes("middleRightWheel"));
	this->backLeftWheel = new Object(loader.getVertices("backLeftWheel"), loader.getHitboxes("backLeftWheel"));
	this->backRightWheel = new Object(loader.getVertices("backRightWheel"), loader.getHitboxes("backRightWheel"));

	this->head->setColor(glm::vec4(0.9, 0.3, 0.3, 1));
	this->body->setColor(glm::vec3(0.3, 0.9, 0.1));
	this->frontLeftWheel->setColor(glm::vec3(0, 0, 1));
	this->frontRightWheel->setColor(glm::vec3(0,0,1));
	this->middleLeftWheel->setColor(glm::vec3(0,0,1));
	this->middleRightWheel->setColor(glm::vec3(0,0,1));
	this->backLeftWheel->setColor(glm::vec3(0,0,1));
	this->backRightWheel->setColor(glm::vec3(0,0,1));
}

void Player::drawObjects()
{
	this->head->draw();
	this->body->draw();
	this->frontLeftWheel->draw();
	this->frontRightWheel->draw();
	this->middleLeftWheel->draw();
	this->middleRightWheel->draw();
	this->backLeftWheel->draw();
	this->backRightWheel->draw();
}

void Player::update()
{
	if (this->keyDown(GLFW_KEY_UP))
	{	
		if (this->speed < this->maxSpeed)
			this->speed += this->acceleration * Base::dt;
	}

	if (this->keyDown(GLFW_KEY_DOWN))
	{
		if (this->speed > -this->maxSpeed)
			this->speed -= this->deceleration * Base::dt;
	}
	if (this->keyDown(GLFW_KEY_LEFT))
	{
		/*this->yaw += this->rotationSpeed * Base::dt;
		if (this->yaw > 360)
			this->yaw -= 360;*/
		this->turnLeft();
	}
	
	if (this->keyDown(GLFW_KEY_RIGHT))
	{
		/*this->yaw -= this->rotationSpeed * Base::dt;
		if (this->yaw < 0)
			this->yaw += 360;*/
		this->turnRight();
	}
	
	//if (this->keyDown(GLFW_KEY_KP_ADD)) this->move(glm::vec3(0, 1, 0) * Base::dt * this->speed);
	//if (this->keyDown(GLFW_KEY_KP_SUBTRACT) && !this->frontLeftWheel->hitbox.checkCollision()) this->move(glm::vec3(0, -1, 0) * Base::dt * this->speed);

	if (this->speed > 0)
		this->speed -= this->drag * Base::dt;
	
	if (this->speed < 0)
		this->speed += this->drag * Base::dt;

	if (abs(this->speed) < this->drag * Base::dt)
		this->speed = 0;

	glm::mat4 fMat(1.f);
	glm::mat4 bMat(1.f);

	glm::vec3 fVec(0.f);
	glm::vec3 bVec(0.f);

	glm::vec3 vec(0.f);

	float rotation = 0;

	if (this->speed > 40) this->friction = 1 - (this->speed - 40) / 20.f;
	else this->friction = 0.95;

	vec = glm::vec3(0.f, 0.f, this->speed * Base::dt);
	rotation = this->wheelYaw * Base::dt * this->speed / this->wheelBase * this->friction;

	fMat = glm::rotate(fMat, glm::radians(this->yaw + rotation), glm::vec3(0.0f, 1.f, 0.0f));
	fMat = glm::translate(fMat, vec);
	fMat = glm::translate(fMat, glm::vec3(0.0f, 0.0f, this->wheelBase / 2.f));

	bMat = glm::rotate(bMat, glm::radians(this->yaw), glm::vec3(0.0f, 1.f, 0.0f));
	bMat = glm::translate(bMat, vec);
	bMat = glm::translate(bMat, glm::vec3(0.0f, 0.0f, -this->wheelBase / 2.f));

	fVec = glm::vec3(fMat * glm::vec4(0.0f, 0.0f, 0.0f, 1.0));
	bVec = glm::vec3(bMat * glm::vec4(0.0f, 0.0f, 0.0f, 1.0));


	vec = (fVec + bVec) / 2.f;


	//std::ofstream save;
	//save.open("dane.txt", std::ios::app);
	//save << this->frontLeftWheel->getOrigin().x << " " << this->frontLeftWheel->getOrigin().z << " " << this->frontRightWheel->getOrigin().x << " " << this->frontRightWheel->getOrigin().z << std::endl;
	//save.close();


	glm::vec3 frontLeftWheelVec = this->lastFrontLeftWheelPos - this->frontLeftWheel->getOrigin();
	this->lastFrontLeftWheelPos = this->frontLeftWheel->getOrigin();

	float frontLeftWheelRot = glm::length(frontLeftWheelVec) * 360 / (2 * glm::pi<float>() * this->wheelRadius);

	//std::cout << frontLeftWheelRot << std::endl;

	this->move(vec);
	this->rotYaw(rotation);

	this->frontLeftWheel->rotByOriginPitch(frontLeftWheelRot);
}

void Player::rotateWheels()
{
	//this->frontLeftWheel->rotByOriginPitch(-100);
	this->frontRightWheel->rotByOriginPitch(-100);
	this->middleLeftWheel->rotByOriginPitch(-100);
	this->middleRightWheel->rotByOriginPitch(-100);
	this->backLeftWheel->rotByOriginPitch(-100);
	this->backRightWheel->rotByOriginPitch(-100);
}

void Player::rotYaw(float angle)
{
	this->yaw += angle;
	this->head->rotYaw(angle);
	this->body->rotYaw(angle);
	this->frontLeftWheel->rotYaw(angle);
	this->frontRightWheel->rotYaw(angle);
	this->middleLeftWheel->rotYaw(angle);
	this->middleRightWheel->rotYaw(angle);
	this->backLeftWheel->rotYaw(angle);
	this->backRightWheel->rotYaw(angle);
}

void Player::setRotYaw(float angle)
{
	this->yaw = angle;
	this->head->setRotYaw(angle);
	this->body->setRotYaw(angle);
	this->frontLeftWheel->setRotYaw(angle);
	this->frontRightWheel->setRotYaw(angle);
	this->middleLeftWheel->setRotYaw(angle);
	this->middleRightWheel->setRotYaw(angle);
	this->backLeftWheel->setRotYaw(angle);
	this->backRightWheel->setRotYaw(angle);
}

void Player::turnLeft()
{
	if (this->wheelYaw > 45) return;
	this->wheelYaw += 100 * Base::dt;
}

void Player::turnRight()
{
	if (this->wheelYaw < -45) return;
	this->wheelYaw -= 100 * Base::dt;
}

bool Player::keyDown(int key)
{
	if (glfwGetKey(Base::window, key) == GLFW_PRESS)
		return true;
	return false;
}

Player::Player(OBJLoader& loader)
{

	this->initObjects(loader);

	this->pos = glm::vec3(0.f);
	
	this->speed = 0;
	this->maxSpeed = 50;
	this->acceleration = 100;
	this->deceleration = 50;
	this->drag = 20;
	this->friction = 0.9;
	this->yaw = 0;
	this->wheelYaw = 0;
	this->wheelBase = abs(glm::distance(this->frontLeftWheel->getOrigin(), this->backLeftWheel->getOrigin()));

	this->lastFrontLeftWheelPos = this->frontLeftWheel->getOrigin();

	this->wheelRadius = this->frontLeftWheel->getSize().y / 2.f;

	
}

Player::~Player()
{
	delete this->head;
	delete this->body;
	delete this->frontLeftWheel;
	delete this->frontRightWheel;
	delete this->middleLeftWheel;
	delete this->middleRightWheel;
	delete this->backLeftWheel;
	delete this->backRightWheel;
}

glm::vec3 Player::getOrigin()
{
	return this->body->getOrigin();
}

float Player::getYaw()
{
	return this->yaw;
}

void Player::move(glm::vec3 vec)
{
	this->pos += vec;
	this->head->move(vec);
	this->body->move(vec);
	this->frontLeftWheel->move(vec);
	this->frontRightWheel->move(vec);
	this->middleLeftWheel->move(vec);
	this->middleRightWheel->move(vec);
	this->backLeftWheel->move(vec);
	this->backRightWheel->move(vec);
}

void Player::setPos(glm::vec3 vec)
{
	this->pos = vec;
	this->head->setPos(vec);
	this->body->setPos(vec);
	this->frontLeftWheel->setPos(vec);
	this->frontRightWheel->setPos(vec);
	this->middleLeftWheel->setPos(vec);
	this->middleRightWheel->setPos(vec);
	this->backLeftWheel->setPos(vec);
	this->backRightWheel->setPos(vec);
}

void Player::draw()
{
	this->update();

	this->rotateWheels();

	this->frontLeftWheel->setRotByOriginYaw(this->wheelYaw);
	this->frontRightWheel->setRotByOriginYaw(this->wheelYaw);

	this->drawObjects();

	
	
	/*this->head->drawHitbox();
	this->body->drawHitbox();
	this->frontLeftWheel->drawHitbox();
	this->frontRightWheel->drawHitbox();
	this->middleLeftWheel->drawHitbox();
	this->middleRightWheel->drawHitbox();
	this->backLeftWheel->drawHitbox();
	this->backRightWheel->drawHitbox();*/


}
