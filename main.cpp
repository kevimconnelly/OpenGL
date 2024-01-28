#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() 
{
	glfwInit();

	// Tell GLFW what version we're using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we're using the core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window and specify size, name
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);

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
	glViewport(0, 0, 800, 800);

	// Specify background color
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// Clear the back buffer and assign new color to it
	glClear(GL_COLOR_BUFFER_BIT);

	// Swap back buffer with front buffer
	glfwSwapBuffers(window);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Have GLFW handle all events
		glfwPollEvents();
	}

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}