#include "Game.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	Game game;

	glfwSetFramebufferSizeCallback(game.getWindow(), framebuffer_size_callback);
	
	while (!glfwWindowShouldClose(game.getWindow()))
	{
		game.run();
	}

	glfwTerminate();

	return 0;
}