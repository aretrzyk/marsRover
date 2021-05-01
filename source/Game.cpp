#include "Game.h"

Game::Game()
{
	//Inicjalizacja GLFW
	if (!glfwInit())
	{
		std::cout << "GLFW INIT ERROR" << std::endl;
	}

	//Ustawienia GLFW
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	this->WINDOW_HEIGHT = 720;
	this->WINDOW_WIDTH = 1280;

	this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, "MARSROVER", NULL, NULL);
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
		//problem glewInit b³¹d, coœ jest na prawdê Ÿle
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	std::cout << glGetString(GL_VERSION) << std::endl;
	std::cout << "Using GLEW: " << glewGetString(GLEW_VERSION) << std::endl;
	;

	//OPEN GL OPTIONS
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	//glEnable(GL_BACK);
	//glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Camera
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	this->camera = new Camera(this->window);
	

	//Shader
	this->coreProgram = new Shader("res/shaders/basicVShader.vert", "res/shaders/basicFShader.frag");
	
	this->test = new Object();
	this->test->loadFromFile("res/models/rover.obj");
}

GLFWwindow* Game::getWindow()
{
	return this->window;
}

void Game::run()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	this->camera->update(this->coreProgram);
	//this->coreProgram->use();
	test->draw(this->camera->viewMatrix(), this->camera->projectionMatrix());

	glfwSwapBuffers(window);
	glfwPollEvents();
}
