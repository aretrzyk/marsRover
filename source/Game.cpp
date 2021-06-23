#include "Game.h"

void Game::updateInput()
{
	if (glfwGetKey(Base::window, GLFW_KEY_C) == GLFW_PRESS)
	{
		if (this->cameraType == 0)
		{
			this->cameraType = 1;
		}
		else
		{
			this->cameraType = 0;
		}
			
	}
		
}

void Game::objectsInit()
{
	//OBJ loader init
	OBJLoader objFloor("res/models/raceMap.obj");
	OBJLoader objCube("res/models/cube.obj");
	OBJLoader objRover("res/models/lazik.obj");

	//Object init
	this->sun = new Object(objCube.getVertices(), objCube.getHitboxes());
	this->map = new Map(objFloor);
	this->rover = new Player(objRover, this->map);

	

	//Objects presets 
	//Rover
	this->rover->move(glm::vec3(0, 1, 0));

	//Sun
	this->sun->setColor(glm::vec4(Base::lightColor, 0.5));
	this->sun->move(glm::vec3(0, 120, 0));
	
	//Floor
	this->map->setColor(glm::vec3(1, 0.2, 0.2));
	this->map->setPos(glm::vec3(0, 0, 0));

}

void Game::drawObjects()
{
	//float x = 20 * cos(glfwGetTime());
	//float z = 5 * sin(glfwGetTime());

	//Base::lightPos = glm::vec3(x, 5, z);

	//this->rover->rotateAboutPoint(glm::vec3(0, 100 * Base::dt, 0), glm::vec3(0, 10, 0));
	this->rover->draw();

	//this->sun->rotate(glm::vec3(0.1f, 0.1f, 0.1f));
	//this->sun->setPos(Base::lightPos + glm::vec3(0.f, 2.f, 0.f));
	//this->sun->drawHitbox();
	//this->sun->draw();

	this->map->draw();

}

Game::Game()
{
	//Inicjalizacja GLFW
	if (!glfwInit())
	{
		std::cout << "GLFW INIT ERROR" << std::endl;
	}

	//Ustawienia GLFW
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	this->WINDOW_HEIGHT = 720;
	this->WINDOW_WIDTH = 1280;

	Base::window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, "SRAMROVER", NULL, NULL);
	if (!Base::window)
	{
		std::cout << "ERROR CREATING WINDOW" << std::endl;
		glfwTerminate();
	}

	this->framebufferHeight = 0;
	this->framebufferWidth = 0;

	glfwGetFramebufferSize(Base::window, &framebufferWidth, &framebufferHeight);
	glViewport(0, 0, framebufferWidth, framebufferHeight);

	glfwMakeContextCurrent(Base::window);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_NO_ERROR != err)
	{
		std::cout << "GLEW ERROR " << glewGetErrorString(err) << std::endl;
	}
	std::cout << glGetString(GL_VERSION) << std::endl;
	std::cout << "Using GLEW: " << glewGetString(GLEW_VERSION) << std::endl;

	//OPEN GL OPTIONS
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Camera
	glfwSetInputMode(Base::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	this->camera = new Camera();
	this->cameraType = 0;
	
	this->objectsInit();
}

Game::~Game()
{
	delete this->camera;
	delete this->sun;
	delete this->map;
	delete this->rover;
}

void Game::run()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	this->updateInput();
	
	if(this->cameraType == 0) this->camera->updateThirdPersCam(this->rover->getOrigin(), -this->rover->getYaw() + 90, 30.f);
	else if(this->cameraType == 1) this->camera->updateFreeCam();

	this->drawObjects();
	

	glfwSwapBuffers(Base::window);
	glfwPollEvents();
}

