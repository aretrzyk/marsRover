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

	/*glm::vec3 origin(0, -1, 0);
	glm::vec3 direction(0, -1, 0);
	glm::vec3 triangle1(-0.5, 0, -0.5);
	glm::vec3 triangle2(0.5, 0, -0.5);
	glm::vec3 triangle3(0, 0, 0.5);
	glm::vec3 triangle21(-0.5, -1, -0.5);
	glm::vec3 triangle22(0.5, -1, -0.5);
	glm::vec3 triangle23(0, -1, 0.5);
	glm::vec3 position(0, 0, 0);
	glm::vec3 position2(0, 0, 0);

	bool result = glm::intersectLineTriangle(origin, direction, triangle1, triangle2, triangle3, position);
	bool result2 = glm::intersectLineTriangle(origin, direction, triangle21, triangle22, triangle23, position2);


	std::cout << result << std::endl;
	std::cout << result2 << std::endl;
	std::cout << position.x << " " << position.y << " " << position.z << std::endl;
	std::cout << position2.x << " " << position2.y << " " << position2.z << std::endl;*/

	glfwTerminate();

	return 0;
}