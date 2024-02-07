#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"

const unsigned int width = 800;
const unsigned int height = 800;

// Define the vertices of the triangle
GLfloat vertices[] =
{
	-0.5f,   0.0f,	  0.5f,		0.83f, 0.70f,  0.44f,		0.0f, 0.0f,  
	-0.5f,   0.0f,	 -0.5f,		0.83f, 0.70f,  0.44f,		5.0f, 0.0f, 
	 0.5f,   0.0f,	 -0.5f,		0.83f, 0.70f,  0.44f,		0.0f, 1.0f,  
	 0.5f,   0.0f,	  0.5f,		0.83f, 0.70f,  0.44f,		5.0f, 0.0f,  
	 0.0f,   0.8f,    0.0f,     0.92f, 0.86f,  0.76f,       2.5f, 5.0f
};

GLuint indices[] =
{
	0, 1, 2, 
	0, 2, 3, 
	0, 1, 4,
	1, 2, 4, 
	2, 3, 4, 
	3, 0, 4
};

int main() 
{
	//Initialize GLFW
	glfwInit();

	// Tell GLFW what version we're using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we're using the core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window and specify size, name
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);

	// Error check in case window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return -1;
	}

	// Introduce window to the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL and its size
	glViewport(0, 0, width, height);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	Texture popCat("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load("brick.png", &widthImg, &heightImg, &numColCh, 0);


	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell openGL which shader program to use
		shaderProgram.Activate();

		camera.Inputs(window); 
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		popCat.Bind();

		// Bind the VAO to openGL knows how to use it
		VAO1.Bind();
		//Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		// Have GLFW handle all events
		glfwPollEvents();
	}

	// Delete all the objects we created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	popCat.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}