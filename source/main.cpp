#include "libs.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{

	#pragma region GLFW AND GLEW INIT
	GLFWwindow* window;

	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;
	int framebufferWidth = 0;
	int framebufferHeight = 0;

	if (!glfwInit())
	{
		return -1;
	}

	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glViewport(0, 0, framebufferWidth, framebufferHeight);

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_NO_ERROR != err)
	{
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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	Camera camera(window);

#pragma endregion

	Shader coreProgram("res/shaders/basicVShader.vert", "res/shaders/basicFShader.frag");

	#pragma region VERTICES
	
	Object triangle;
	triangle.appendVertex(Vertex(glm::vec3(-0.5, -0.5, 0.5), glm::vec3(1, 1, 0), glm::vec2(0, 0)));
	triangle.appendVertex(Vertex(glm::vec3(0.5, -0.5, 0.5), glm::vec3(1, 1, 0), glm::vec2(1, 0)));
	triangle.appendVertex(Vertex(glm::vec3(0.5, 0.5, 0.5), glm::vec3(1, 1, 0), glm::vec2(1, 1)));
	triangle.appendVertex(Vertex(glm::vec3(0.5, 0.5, 0.5), glm::vec3(1, 1, 0), glm::vec2(1, 1)));
	triangle.appendVertex(Vertex(glm::vec3(-0.5, 0.5, 0.5), glm::vec3(1, 1, 0), glm::vec2(0, 1)));
	triangle.appendVertex(Vertex(glm::vec3(-0.5, -0.5, 0.5), glm::vec3(1, 1, 0), glm::vec2(0, 0)));

	triangle.appendVertex(Vertex(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(1, 1, 0), glm::vec2(0, 0)));
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
	
	//triangle.outputToFile("primitives/cube.txt");
#pragma endregion

	#pragma region TEXTURES

	int textureWidth = 0;
	int textureHeight = 0; 
	unsigned char* dirtImage = SOIL_load_image("res/textures/dirt.jpg", &textureWidth, &textureHeight, NULL, SOIL_LOAD_RGB);

	unsigned int dirtTexture;
	glGenTextures(1, &dirtTexture);
	glBindTexture(GL_TEXTURE_2D, dirtTexture);

	if (dirtImage)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, dirtImage);;
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	}
	else
	{
		std::cout << "Error loading texture" << std::endl;
	}

	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(dirtImage);

#pragma endregion

	#pragma region BUFFERS
	//VAO
	unsigned int VAO;
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * triangle.vNr(), triangle.ver(), GL_STATIC_DRAW);

	//EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * triangle.iNr(), triangle.ind(), GL_STATIC_DRAW);

	//VERTEXATTRIBPOINTERS
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

#pragma endregion

	#pragma region MODEL MATRIX

	glm::vec3 translationVec(1.0f);
	glm::vec3 rotationVec(1.0f);
	glm::vec3 scaleVec(1.f);

	glm::vec3 translationVec2(1.0f);
	glm::vec3 rotationVec2(1.0f);
	glm::vec3 scaleVec2(1.f);

	glm::mat4 ModelMatrix(1.f);
	ModelMatrix = glm::translate(ModelMatrix, translationVec);
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotationVec.x), glm::vec3(1.f, 0.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotationVec.y), glm::vec3(0.f, 1.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotationVec.z), glm::vec3(0.f, 0.f, 1.f));
	ModelMatrix = glm::scale(ModelMatrix, scaleVec);
	glm::mat4 ModelMatrix2(1.f);
	ModelMatrix2 = glm::translate(ModelMatrix2, translationVec2);
	ModelMatrix2 = glm::rotate(ModelMatrix2, glm::radians(rotationVec2.x), glm::vec3(1.f, 0.f, 0.f));
	ModelMatrix2 = glm::rotate(ModelMatrix2, glm::radians(rotationVec2.y), glm::vec3(0.f, 1.f, 0.f));
	ModelMatrix2 = glm::rotate(ModelMatrix2, glm::radians(rotationVec2.z), glm::vec3(0.f, 0.f, 1.f));
	ModelMatrix2 = glm::scale(ModelMatrix2, scaleVec2);


	coreProgram.setUni4fm("ModelMatrix", ModelMatrix);



#pragma endregion

	
	coreProgram.use();
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, dirtTexture);

	translationVec = glm::vec3(3.f, 0.f, 0.f);
	translationVec2 = glm::vec3(-3.f, 0.f, 0.f);
	
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		camera.update(&coreProgram);
		rotationVec.x += 0.1f;
		rotationVec.y += 0.1f;

		rotationVec2.x += 0.1f;
		rotationVec2.y += 0.1f;

		ModelMatrix = glm::mat4(1.0f);
		ModelMatrix = glm::translate(ModelMatrix, translationVec);
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotationVec.x), glm::vec3(1.f, 0.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotationVec.y), glm::vec3(0.f, 1.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotationVec.z), glm::vec3(0.f, 0.f, 1.f));
		ModelMatrix = glm::scale(ModelMatrix, scaleVec);
		coreProgram.setUni4fm("ModelMatrix", ModelMatrix);
		coreProgram.use();
		glDrawElements(GL_TRIANGLES, triangle.iNr(), GL_UNSIGNED_INT, 0);

		ModelMatrix2 = glm::mat4(1.0f);
		ModelMatrix2 = glm::translate(ModelMatrix2, translationVec2);
		ModelMatrix2 = glm::rotate(ModelMatrix2, glm::radians(rotationVec2.x), glm::vec3(1.f, 0.f, 0.f));
		ModelMatrix2 = glm::rotate(ModelMatrix2, glm::radians(rotationVec2.y), glm::vec3(0.f, 1.f, 0.f));
		ModelMatrix2 = glm::rotate(ModelMatrix2, glm::radians(rotationVec2.z), glm::vec3(0.f, 0.f, 1.f));
		ModelMatrix2 = glm::scale(ModelMatrix2, scaleVec2);
		coreProgram.setUni4fm("ModelMatrix", ModelMatrix2);
		coreProgram.use();
		glDrawElements(GL_TRIANGLES, triangle.iNr(), GL_UNSIGNED_INT, 0);

		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}