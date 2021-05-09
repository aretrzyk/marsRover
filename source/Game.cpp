#include "Game.h"

void Game::objectsInit()
{

	OBJLoader vCube("res/models/cube.obj");
	OBJLoader vFloor("res/models/testFloor.obj");
	OBJLoader vRover("res/models/azik47.obj");

	

	this->test = new Object;
	this->test->load(vRover.getVertices("body"));

	this->test->setColor(glm::vec3(0.2, 0.8, 0.2));
	//this->test->move(glm::vec3(0.0, 2, 0.0));


	this->sun = new Object;
	this->sun->load(vCube.getVertices());

	//this->sun->scale(glm::vec3(0.1f));
	this->sun->setColor(glm::vec4(Base::lightColor, 0.5));
	
	this->floor = new Object;
	this->floor->load(vFloor.getVertices());

	this->floor->setColor(glm::vec3(1, 0.2, 0.2));
	this->floor->move(glm::vec3(0, 0, 0));

	this->rover = new Player(vRover);
	//this->rover = new Player(vRover.getVertices("body"));

}

void Game::drawObjects()
{
	
	//this->test->draw();

	float x = 20 * cos(glfwGetTime());
	float z = 5 * sin(glfwGetTime());

	Base::lightPos = glm::vec3(x, 5, z);
	
	this->sun->rotate(glm::vec3(0.1f, 0.1f, 0.1f));
	this->sun->move(Base::lightPos + glm::vec3(0.f, 2.f, 0.f));
	this->sun->draw();

	this->floor->draw();
	//this->rover->head.draw();

	this->rover->draw();
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

	this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, "SRAMROVER", NULL, NULL);
	if (!this->window)
	{
		std::cout << "ERROR CREATING WINDOW" << std::endl;
		glfwTerminate();
	}

	this->framebufferHeight = 0;
	this->framebufferWidth = 0;

	glfwGetFramebufferSize(this->window, &framebufferWidth, &framebufferHeight);
	glViewport(0, 0, framebufferWidth, framebufferHeight);

	glfwMakeContextCurrent(this->window);

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
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	this->camera = new Camera(this->window);
	
	this->objectsInit();
}

Game::~Game()
{
	delete this->camera;
	//delete this->test;
	delete this->floor;
	delete this->rover;
}

GLFWwindow* Game::getWindow()
{
	return this->window;
}

void Game::run()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	this->camera->update();

	this->drawObjects();

	glfwSwapBuffers(window);
	glfwPollEvents();
}

