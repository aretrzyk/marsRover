#include "Player.h"

void Player::loadObjects(OBJLoader loader)
{
	this->head.load(loader.getVertices("head"));
	this->body.load(loader.getVertices("body"));
	this->frontLeftWheel.load(loader.getVertices("frontLeftWheel"));
	this->frontRightWheel.load(loader.getVertices("frontRightWheel"));
	this->middleLeftWheel.load(loader.getVertices("middleLeftWheel"));
	this->middleRightWheel.load(loader.getVertices("middleRightWheel"));
	this->backLeftWheel.load(loader.getVertices("backLeftWheel"));
	this->backRightWheel.load(loader.getVertices("backRightWheel"));
}

void Player::drawObjects()
{
	this->head.draw();
	this->body.draw();
	this->frontLeftWheel.draw();
	this->frontRightWheel.draw();
	this->middleLeftWheel.draw();
	this->middleRightWheel.draw();
	this->backLeftWheel.draw();
	this->backRightWheel.draw();
}

Player::Player(OBJLoader loader)
{
	this->loadObjects(loader);
}
Player::Player(std::vector<Vertex>& vertices)
{
	this->head.load(vertices);
}
void Player::draw()
{
	//this->frontLeftWheel.rotate(glm::vec3(0.1, 0.0, 0.0));
	this->head.setColor(glm::vec4(1, 1, 1, 1));
	this->head.move(glm::vec3(0.0, 2.0, 0.0));
	this->drawObjects();

	//this->head.draw();
}
