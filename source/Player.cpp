#include "Player.h"

void Player::initObjects(OBJLoader& loader)
{
	this->head = new Object;
	this->body = new Object;
	this->frontLeftWheel = new Object;
	this->frontRightWheel = new Object;
	this->middleLeftWheel = new Object;
	this->middleRightWheel = new Object;
	this->backLeftWheel = new Object;
	this->backRightWheel = new Object;

	this->head->load(loader.getVertices("head"));
	this->body->load(loader.getVertices("body"));
	this->frontLeftWheel->load(loader.getVertices("frontLeftWheel"));
	this->frontRightWheel->load(loader.getVertices("frontRightWheel"));
	this->middleLeftWheel->load(loader.getVertices("middleLeftWheel"));
	this->middleRightWheel->load(loader.getVertices("middleRightWheel"));
	this->backLeftWheel->load(loader.getVertices("backLeftWheel"));
	this->backRightWheel->load(loader.getVertices("backRightWheel"));

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
	this->frontLeftWheel->rotate(glm::vec3(0, 0, 0.15));
	this->frontRightWheel->rotate(glm::vec3(0, 0, -0.13));
	this->middleLeftWheel->rotate(glm::vec3(0, 0, -0.16));
	this->middleRightWheel->rotate(glm::vec3(0, 0, 0.12));
	this->backLeftWheel->rotate(glm::vec3(0, 0, -0.1));
	this->backRightWheel->rotate(glm::vec3(0, 0, 0.08));
	this->head->rotate(glm::vec3(0.1, 0.1, 0.1));
	this->body->rotate(glm::vec3(1, 1, 1));
	
	this->drawObjects();
}
