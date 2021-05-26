#include "Game.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)glfwSetWindowShouldClose(window, true);
}

int main()
{
	Game game;

	glfwSetFramebufferSizeCallback(Base::window, framebuffer_size_callback);
	
	while (!glfwWindowShouldClose(Base::window))
	{
		processInput(Base::window);
		game.run();
	}

	glfwTerminate();

	return 0;
}