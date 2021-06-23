#include "Player.h"

void Player::setY(float y)
{
	this->pos.y = y;
	this->head->setY(y);
	this->body->setY(y);
	this->frontLeftWheel->setY(y);
	this->frontRightWheel->setY(y);
	this->middleLeftWheel->setY(y);
	this->middleRightWheel->setY(y);
	this->backLeftWheel->setY(y);
	this->backRightWheel->setY(y);
}

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
		this->turnLeft();
	}
	if (this->keyDown(GLFW_KEY_RIGHT))
	{

		this->turnRight();
	}

	if (this->speed > 0)
		this->speed -= this->drag * Base::dt;

	if (this->speed < 0)
		this->speed += this->drag * Base::dt;

	if (abs(this->speed) < this->drag * Base::dt)
		this->speed = 0;

	float gravityStrength = 30.f;



	glm::vec3 moveVec(0.f, 0.f, this->speed * Base::dt);
	//glm::vec3 moveVec = glm::normalize(glm::cross(this->pos, glm::vec3(-1.f, 0.f, 0.f))) * this->speed * Base::dt;
	float rotation = this->wheelYaw * Base::dt * this->speed / this->wheelBase * this->friction;

	glm::vec3 gravityVec = glm::vec3(0.f, -1.f, 0.f) * Base::dt * gravityStrength;
	//glm::vec3 gravityVec = -glm::normalize(this->pos) * Base::dt * gravityStrength;

	glm::vec3 heightVec = glm::vec3(0.f, 5.f, 0.f);

	glm::vec3 frontLeftVec(-this->wheelDistance / 2.f, 0.f, this->wheelBase / 2.f);
	glm::vec3 frontRightVec(this->wheelDistance / 2.f, 0.f, this->wheelBase / 2.f);
	glm::vec3 backLeftVec(-this->wheelDistance / 2.f, 0.f, -this->wheelBase / 2.f);
	glm::vec3 backRightVec(this->wheelDistance / 2.f, 0.f, -this->wheelBase / 2.f);

	glm::mat4 frontMat(1.f);
	glm::mat4 backMat(1.f);

	frontMat = glm::rotate(frontMat, glm::radians(this->yaw + this->wheelYaw), glm::vec3(0.f, 1.f, 0.f));
	//frontMat = glm::rotate(frontMat, glm::radians(this->pitch), glm::vec3(1.f, 0.f, 0.f));
	//frontMat = glm::rotate(frontMat, glm::radians(this->roll), glm::vec3(0.f, 0.f, 1.f));
	frontMat = glm::translate(frontMat, moveVec);

	backMat = glm::rotate(backMat, glm::radians(this->yaw), glm::vec3(0.f, 1.f, 0.f));
	//backMat = glm::rotate(backMat, glm::radians(this->roll), glm::vec3(0.f, 0.f, 1.f));
	//backMat = glm::rotate(backMat, glm::radians(this->pitch), glm::vec3(1.f, 0.f, 0.f));
	backMat = glm::translate(backMat, moveVec);

	frontLeftVec = glm::vec3(frontMat * glm::vec4(0.f, 0.f, 0.f, 1.f));
	frontRightVec = glm::vec3(frontMat * glm::vec4(0.f, 0.f, 0.f, 1.f));

	backLeftVec = glm::vec3(backMat * glm::vec4(0.f, 0.f, 0.f, 1.f));
	backRightVec = glm::vec3(backMat * glm::vec4(0.f, 0.f, 0.f, 1.f));

	glm::vec3 frontVec = (frontLeftVec + frontRightVec) / 2.f;
	glm::vec3 backVec = (backLeftVec + backRightVec) / 2.f;
	moveVec = (frontVec + backVec) / 2.f;

	glm::vec3 centerPos = moveVec + this->pos - heightVec;
	glm::vec3 frontLeftPos = frontLeftVec + this->frontLeftWheel->getOrigin() - heightVec;
	glm::vec3 frontRightPos = frontRightVec + this->frontRightWheel->getOrigin() - heightVec;
	glm::vec3 backLeftPos = backLeftVec + this->backLeftWheel->getOrigin() - heightVec;
	glm::vec3 backRightPos = backRightVec + this->backRightWheel->getOrigin() - heightVec;

	glm::vec3 centerCollisionVec = this->map->checkCollision(
		centerPos,
		gravityVec,
		1
	);
	glm::vec3 frontLeftCollisionVec = this->map->checkCollision(
		frontLeftPos,
		gravityVec,
		2
	);
	glm::vec3 frontRightCollisionVec = this->map->checkCollision(
		frontRightPos,
		gravityVec,
		2
	);
	glm::vec3 backLeftCollisionVec = this->map->checkCollision(
		backLeftPos,
		gravityVec,
		2
	);
	glm::vec3 backRightCollisionVec = this->map->checkCollision(
		backRightPos,
		gravityVec,
		2
	);

	if(glm::length(gravityVec + frontLeftCollisionVec) > 5 * Base::dt)
	frontLeftPos += gravityVec + frontLeftCollisionVec;

	if (glm::length(gravityVec + frontRightCollisionVec) > 5 * Base::dt)
	frontRightPos += gravityVec + frontRightCollisionVec;

	if (glm::length(gravityVec + backLeftCollisionVec) > 5 * Base::dt)
	backLeftPos += gravityVec + backLeftCollisionVec;

	if (glm::length(gravityVec + backRightCollisionVec) > 5 * Base::dt)
	backRightPos += gravityVec + backRightCollisionVec;

	if (glm::length(gravityVec + centerCollisionVec) > 5 * Base::dt)
	moveVec += gravityVec + centerCollisionVec;

	//std::cout << frontLeftPos.x << " " << frontLeftPos.y << " " << frontLeftPos.z << std::endl;

	float wheelBase = sqrt(pow(frontLeftPos.x - backLeftPos.x, 2) + pow(frontLeftPos.z - backLeftPos.z, 2));
	float wheelDistance = sqrt(pow(frontLeftPos.x - frontRightPos.x, 2) + pow(frontLeftPos.z - frontRightPos.z, 2));

	float leftPitch = -glm::degrees(atan((frontLeftPos.y - backLeftPos.y) / wheelBase));
	float rightPitch = -glm::degrees(atan((frontRightPos.y - backRightPos.y) / wheelBase));
	float pitch = (leftPitch + rightPitch) / 2.f;

	float frontRoll = glm::degrees(atan((frontLeftPos.y - frontRightPos.y) / wheelDistance));
	float backRoll = glm::degrees(atan((backLeftPos.y - backRightPos.y) / wheelDistance));
	float roll = (frontRoll + backRoll) / 2.f;

	//std::cout << this->pitch << std::endl;

	this->move(moveVec);
	this->rotYaw(rotation);
	this->setPitch(pitch);
	this->setRoll(roll);
	Base::lightPos = this->pos + glm::vec3(0.f, 5.f, 0.f);
	//std::cout << this->pos.x << " " << this->pos.y << " " << this->pos.z << std::endl;

	











	//float gravityStrength = 10.f;

	//glm::mat4 frontMat = glm::mat4(1.f);
	//glm::mat4 backMat = glm::mat4(1.f);

	//glm::vec3 moveVec = glm::vec3(0.f, 0.f, 1.f) * this->speed;
	//float rotation = this->wheelYaw * Base::dt * this->speed / this->wheelBase * this->friction;

	////frontMat = glm::translate(frontMat, glm::vec3(0.f, -gravityStrength * 1.f, 0.f));
	//frontMat = glm::rotate(frontMat, glm::radians(this->yaw + this->wheelYaw), glm::vec3(0.f, 1.f, 0.f));
	////frontMat = glm::rotate(frontMat, glm::radians(this->roll), glm::vec3(0.f, 0.f, 1.f));
	////frontMat = glm::rotate(frontMat, glm::radians(this->pitch), glm::vec3(1.f, 0.f, 0.f));
	//frontMat = glm::translate(frontMat, moveVec);

	////backMat = glm::translate(backMat, glm::vec3(0.f, -gravityStrength * 1.f, 0.f));
	//backMat = glm::rotate(backMat, glm::radians(this->yaw), glm::vec3(0.f, 1.f, 0.f));
	////backMat = glm::rotate(backMat, glm::radians(this->roll), glm::vec3(0.f, 0.f, 1.f));
	////backMat = glm::rotate(backMat, glm::radians(this->pitch), glm::vec3(1.f, 0.f, 0.f));
	//backMat = glm::translate(backMat, moveVec);

	//glm::vec3 frontMoveVec = glm::vec3(frontMat * glm::vec4(0.f, 0.f, 0.f, 1.f)) + glm::vec3(0.f, -gravityStrength * 1.f, 0.f);
	//glm::vec3 backMoveVec = glm::vec3(backMat * glm::vec4(0.f, 0.f, 0.f, 1.f)) + glm::vec3(0.f, -gravityStrength * 1.f, 0.f);

	//moveVec = (frontMoveVec + backMoveVec) / 2.f;
	//
	//moveVec *= Base::dt;
	//frontMoveVec *= Base::dt;
	//backMoveVec *= Base::dt;

	//glm::vec3 frontLeftCollisionVec = this->map->checkCollision(
	//	this->frontLeftWheel->getOrigin(),
	//	frontMoveVec
	//);
	//glm::vec3 frontRightCollisionVec = this->map->checkCollision(
	//	this->frontRightWheel->getOrigin(),
	//	frontMoveVec
	//);
	//glm::vec3 backLeftCollisionVec = this->map->checkCollision(
	//	this->backLeftWheel->getOrigin(),
	//	backMoveVec
	//);
	//glm::vec3 backRightCollisionVec = this->map->checkCollision(
	//	this->backRightWheel->getOrigin(),
	//	backMoveVec
	//);
	//glm::vec3 posCollisionVec = this->map->checkCollision(
	//	this->pos,
	//	moveVec
	//);

	//std::cout << this->pos.x << " " << this->pos.y << " " << this->pos.z << std::endl;

	//this->rotateWheels();
	//this->move(moveVec + posCollisionVec);
	//this->rotYaw(rotation);







	//glm::mat4 fMat(1.f);
	//glm::mat4 bMat(1.f);

	//glm::vec3 fVec(0.f);
	//glm::vec3 bVec(0.f);

	//glm::vec3 vec(0.f);

	//float rotation = 0;
	//float round = 10000.f;

	//if (this->speed > 40) this->friction = 1 - (this->speed - 40) / 20.f;
	//else this->friction = 0.95;

	//vec = glm::vec3(0.f, 0.f, this->speed * Base::dt);
	//rotation = this->wheelYaw * Base::dt * this->speed / this->wheelBase * this->friction;

	//fMat = glm::rotate(fMat, glm::radians(this->yaw + rotation), glm::vec3(0.0f, 1.f, 0.0f));
	//fMat = glm::translate(fMat, vec);
	//fMat = glm::translate(fMat, glm::vec3(0.0f, 0.0f, this->wheelBase / 2.f));

	//bMat = glm::rotate(bMat, glm::radians(this->yaw), glm::vec3(0.0f, 1.f, 0.0f));
	//bMat = glm::translate(bMat, vec);
	//bMat = glm::translate(bMat, glm::vec3(0.0f, 0.0f, -this->wheelBase / 2.f));

	//fVec = glm::vec3(fMat * glm::vec4(0.0f, 0.0f, 0.0f, 1.0));
	//bVec = glm::vec3(bMat * glm::vec4(0.0f, 0.0f, 0.0f, 1.0));

	//vec = (fVec + bVec) / 2.f;

	//this->move(vec);

	//

	///*if (heightFront > heightBack)
	//{
	//	if (heightOrigin < heightFront)
	//		this->pitch = -glm::degrees(atan((heightFront - heightBack) / this->wheelBase));
	//}
	//else if (heightBack > heightFront)
	//{
	//	if (heightOrigin < heightBack)
	//		this->pitch = -glm::degrees(atan((heightFront - heightBack) / this->wheelBase));
	//}

	//if (heightRight > heightLeft)
	//{
	//	if (heightOrigin < heightRight)
	//		this->roll = glm::degrees(atan((heightLeft - heightRight) / this->wheelDistance));
	//}
	//else if (heightLeft > heightRight)
	//{
	//	if (heightOrigin < heightLeft)
	//		this->roll = glm::degrees(atan((heightLeft - heightRight) / this->wheelDistance));
	//}*/

	///*float leftPitch = this->pitch;
	//float rightPitch = this->pitch;

	//if (leftFrontHeight > leftBackHeight)
	//{
	//	if (originHeight < leftFrontHeight)
	//		leftPitch = -glm::degrees(atan((leftFrontHeight - leftBackHeight) / this->wheelBase));
	//}
	//else if (leftBackHeight > leftFrontHeight)
	//{
	//	if (originHeight < leftBackHeight)
	//		leftPitch = -glm::degrees(atan((leftFrontHeight - leftBackHeight) / this->wheelBase));
	//}
	//else leftPitch = 0.f;

	//if (rightFrontHeight > rightBackHeight)
	//{
	//	if (originHeight < rightFrontHeight)
	//		rightPitch = -glm::degrees(atan((rightFrontHeight - rightBackHeight) / this->wheelBase));
	//}
	//else if (rightBackHeight > rightFrontHeight)
	//{
	//	if (originHeight < rightBackHeight)
	//		rightPitch = -glm::degrees(atan((rightFrontHeight - rightBackHeight) / this->wheelBase));
	//}
	//else rightPitch = 0.f;

	//float frontRoll = this->roll;
	//float backRoll = this->roll;

	//if (leftFrontHeight > rightFrontHeight)
	//{
	//	if (originHeight < leftFrontHeight)
	//		frontRoll = glm::degrees(atan((leftFrontHeight - rightFrontHeight) / this->wheelDistance));
	//}
	//else if (rightFrontHeight > leftFrontHeight)
	//{
	//	if (originHeight < rightFrontHeight)
	//		frontRoll = glm::degrees(atan((leftFrontHeight - rightFrontHeight) / this->wheelDistance));
	//}
	//else frontRoll = 0.f;

	//if (leftBackHeight > rightBackHeight)
	//{
	//	if (originHeight < leftBackHeight)
	//		backRoll = glm::degrees(atan((leftBackHeight - rightBackHeight) / this->wheelDistance));
	//}
	//else if (rightBackHeight > leftBackHeight)
	//{
	//	if (originHeight < rightBackHeight)
	//		backRoll = glm::degrees(atan((leftBackHeight - rightBackHeight) / this->wheelDistance));
	//}
	//else backRoll = 0.f;


	//float height = (leftFrontHeight + rightFrontHeight + leftBackHeight + rightBackHeight) / 4;

	//if (height < originHeight) height = originHeight;

	//std::cout << height << std::endl;*/

	//

	///*std::cout <<
	//	centerCollisionVec.x + gravity.x << " " <<
	//	centerCollisionVec.y + gravity.y << " " <<
	//	centerCollisionVec.z + gravity.z << std::endl;*/

	//this->rotateWheels();
	//this->move(glm::round((centerCollisionVec + gravity) * round) / round);
	//this->rotYaw(rotation);
	//this->setPitch(glm::round(pitch * round) / round);
	//this->setRoll(glm::round(roll * round) / round);

}

void Player::rotateWheels()
{

	glm::vec3 frontLeftWheelVec = this->lastFrontLeftWheelPos - this->frontLeftWheel->getOrigin();
	glm::vec3 frontRightWheelVec = this->lastFrontRightWheelPos - this->frontRightWheel->getOrigin();

	glm::vec3 middleLeftWheelVec = this->lastMiddleLeftWheelPos - this->middleLeftWheel->getOrigin();
	glm::vec3 middleRightWheelVec = this->lastMiddleRightWheelPos - this->middleRightWheel->getOrigin();

	glm::vec3 backLeftWheelVec = this->lastBackLeftWheelPos - this->backLeftWheel->getOrigin();
	glm::vec3 backRightWheelVec = this->lastBackRightWheelPos - this->backRightWheel->getOrigin();

	this->lastFrontLeftWheelPos = this->frontLeftWheel->getOrigin();
	this->lastFrontRightWheelPos = this->frontRightWheel->getOrigin();

	this->lastMiddleLeftWheelPos = this->middleLeftWheel->getOrigin();
	this->lastMiddleRightWheelPos = this->middleRightWheel->getOrigin();

	this->lastBackLeftWheelPos = this->backLeftWheel->getOrigin();
	this->lastBackRightWheelPos = this->backRightWheel->getOrigin();

	float value = 360 / (2 * glm::pi<float>() * this->wheelRadius);

	if (this->speed < 0) value = -value;

	float frontLeftWheelRot = glm::length(frontLeftWheelVec) * value;
	float frontRightWheelRot = glm::length(frontRightWheelVec) * value;

	float middleLeftWheelRot = glm::length(middleLeftWheelVec) * value;
	float middleRightWheelRot = glm::length(middleRightWheelVec) * value;

	float backLeftWheelRot = glm::length(backLeftWheelVec) * value;
	float backRightWheelRot = glm::length(backRightWheelVec) * value;

	this->frontLeftWheel->rotByOriginPitch(frontLeftWheelRot);
	this->frontRightWheel->rotByOriginPitch(frontRightWheelRot);
	this->middleLeftWheel->rotByOriginPitch(middleLeftWheelRot);
	this->middleRightWheel->rotByOriginPitch(middleRightWheelRot);
	this->backLeftWheel->rotByOriginPitch(backLeftWheelRot);
	this->backRightWheel->rotByOriginPitch(backRightWheelRot);
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

void Player::setYaw(float angle)
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

void Player::setPitch(float angle)
{
	this->pitch = angle;
	this->head->setRotPitch(angle);
	this->body->setRotPitch(angle);
	this->frontLeftWheel->setRotPitch(angle);
	this->frontRightWheel->setRotPitch(angle);
	this->middleLeftWheel->setRotPitch(angle);
	this->middleRightWheel->setRotPitch(angle);
	this->backLeftWheel->setRotPitch(angle);
	this->backRightWheel->setRotPitch(angle);
}

void Player::setRoll(float angle)
{
	this->roll = angle;
	this->head->setRotRoll(angle);
	this->body->setRotRoll(angle);
	this->frontLeftWheel->setRotRoll(angle);
	this->frontRightWheel->setRotRoll(angle);
	this->middleLeftWheel->setRotRoll(angle);
	this->middleRightWheel->setRotRoll(angle);
	this->backLeftWheel->setRotRoll(angle);
	this->backRightWheel->setRotRoll(angle);
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

Player::Player(OBJLoader& loader, Map* map)
{
	this->initObjects(loader);

	this->pos = glm::vec3(0.f, 0.f, 0.f);
	this->yaw = 0;
	this->pitch = 0;
	this->roll = 0;
	
	this->speed = 0;
	this->maxSpeed = 50;
	this->acceleration = 100;
	this->deceleration = 50;
	this->drag = 20;
	this->friction = 0.9;
	
	this->wheelYaw = 0;
	this->wheelBase = abs(glm::distance(this->frontLeftWheel->getOrigin(), this->backLeftWheel->getOrigin()));
	this->wheelDistance = abs(glm::distance(this->frontLeftWheel->getOrigin(), this->frontRightWheel->getOrigin()));

	this->lastFrontLeftWheelPos = this->frontLeftWheel->getOrigin();

	this->wheelRadius = this->frontLeftWheel->getSize().y / 2.f;

	this->map = map;
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