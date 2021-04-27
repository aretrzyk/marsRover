#include "Game.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	Game game;

	glfwSetFramebufferSizeCallback(game.getWindow(), framebuffer_size_callback);

	#pragma region VERTICES
	
	Object triangle;
	glm::vec3 vertices[6] = { 
		glm::vec3(-0.5, -0.5, 0.5),
		glm::vec3(0.5, -0.5, 0.5),
		glm::vec3(0.5, 0.5, 0.5),
		glm::vec3(0.5, 0.5, 0.5),
		glm::vec3(-0.5, 0.5, 0.5),
		glm::vec3(-0.5, -0.5, 0.5) };

	/*triangle.appendVertex(Vertex(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(1, 1, 0), glm::vec2(0, 0)));
	triangle.appendVertex(Vertex(glm::vec3(0.5, -0.5, -0.5), glm::vec3(1, 1, 0), glm::vec2(1, 0)));
	triangle.appendVertex(Vertex(glm::vec3(0.5, 0.5, -0.5), glm::vec3(1, 1, 0), glm::vec2(1, 1)));
	triangle.appendVertex(Vertex(glm::vec3(0.5, 0.5, -0.5), glm::vec3(1, 1, 0), glm::vec2(1, 1)));
	triangle.appendVertex(Vertex(glm::vec3(-0.5, 0.5, -0.5), glm::vec3(1, 1, 0), glm::vec2(0, 1)));
	triangle.appendVertex(Vertex(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(1, 1, 0), glm::vec2(0, 0)));

	triangle.appendVertex(4);
	triangle.appendVertex(0);
	triangle.appendVertex(3);
	triangle.appendVertex(3);
	triangle.appendVertex(7);
	triangle.appendVertex(4);
	
	triangle.appendVertex(1);
	triangle.appendVertex(5);
	triangle.appendVertex(6);
	triangle.appendVertex(6);
	triangle.appendVertex(2);
	triangle.appendVertex(1);

	triangle.appendVertex(3);
	triangle.appendVertex(2);
	triangle.appendVertex(6);
	triangle.appendVertex(6);
	triangle.appendVertex(7);
	triangle.appendVertex(3);

	triangle.appendVertex(4);
	triangle.appendVertex(5);
	triangle.appendVertex(1);
	triangle.appendVertex(1);
	triangle.appendVertex(0);
	triangle.appendVertex(4);
	*/
#pragma endregion


	#pragma region BUFFERS
	////VAO
	unsigned int VAO;
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	////VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 6, vertices, GL_STATIC_DRAW);

	////EBO
	//unsigned int EBO;
	//lGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * triangle.iNr(), triangle.ind(), GL_STATIC_DRAW);

	////VERTEXATTRIBPOINTERS
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	//glEnableVertexAttribArray(1);

	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
	//glEnableVertexAttribArray(2);

	//glBindVertexArray(0);

#pragma endregion

	
	while (!glfwWindowShouldClose(game.getWindow()))
	{
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		game.run();
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		//glfwSwapBuffers(game.getWindow());
		//glfwPollEvents();
		
	}

	glfwTerminate();

	return 0;
}