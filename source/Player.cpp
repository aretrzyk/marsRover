#include "Player.h"

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

Player::Player(OBJLoader& loader)
{
	this->initObjects(loader);
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

void Player::move(glm::vec3 vec)
{
	this->head->move(vec);
	this->body->move(vec);
	this->frontLeftWheel->move(vec);
	this->frontRightWheel->move(vec);
	this->middleLeftWheel->move(vec);
	this->middleRightWheel->move(vec);
	this->backLeftWheel->move(vec);
	this->backRightWheel->move(vec);
}

void Player::draw()
{
	this->frontLeftWheel->rotate(glm::vec3(-0.1, 0, 0));
	this->frontRightWheel->rotate(glm::vec3(-0.1, 0, 0));
	this->middleLeftWheel->rotate(glm::vec3(-0.1, 0, 0));
	this->middleRightWheel->rotate(glm::vec3(-0.1, 0, 0));
	this->backLeftWheel->rotate(glm::vec3(-0.1, 0, 0));
	this->backRightWheel->rotate(glm::vec3(-0.1, 0, 0));
	//this->head->rotate(glm::vec3(0.1, 0.1, 0.1));
	//this->body->rotate(glm::vec3(1, 1, 1));
	
	this->head->drawHitbox();
	this->body->drawHitbox();
	this->frontLeftWheel->drawHitbox();
	this->frontRightWheel->drawHitbox();
	this->middleLeftWheel->drawHitbox();
	this->middleRightWheel->drawHitbox();
	this->backLeftWheel->drawHitbox();
	this->backRightWheel->drawHitbox();


	this->drawObjects();
}
