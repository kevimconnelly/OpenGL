#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


// Define the positions of the vertex and fragment shaders
const char* vertexShaderSource = "#version 330 core \n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z 1.0;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main() 
{
	//Initialize GLFW
	glfwInit();

	// Tell GLFW what version we're using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we're using the core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Define the vertices of the triangle
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};

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


	// Create vertex shader and pass source to it
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the vertex shader
	glCompileShader(vertexShader);


	//Create the fragment shader and pass source to it
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//Comile the fragment shader
	glCompileShader(fragmentShader);


	// Create the shader program object and get its reference
	GLuint shaderProgram = glCreateProgram();


	// Attach the shaders to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	//Wrap up all shaders together in the shader program
	glLinkProgram(shaderProgram);


	//Delete the shader objects since theve already been attached and linked to the shader program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Create reference containers for the vertex array object and the vertex buffer object
	GLuint VAO, VBO;

	// Generate the VAO and VBO with 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	//Make the VAO the current vertex array object by binding it
	glBindVertexArray(VAO);
	// Bind the VBO specifiying its a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure the vertex attribute so OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the vertex attribute so that opengl knows how to use it
	glEnableVertexAttribArray(0);


	// Bind the VAO and VBO to 0 so we dont accidentally modify them
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Specify background color
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// Clear the back buffer and assign new color to it
	glClear(GL_COLOR_BUFFER_BIT);

	// Swap back buffer with front buffer
	glfwSwapBuffers(window);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell openGL which shader program to use
		glUseProgram(shaderProgram);
		// Bind the VAO to openGL knows how to use it
		glBindVertexArray(VAO);
		//Draw the triangle using the GL_TRIANGLES primitive
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		// Have GLFW handle all events
		glfwPollEvents();
	}


	// Delete all the objects we created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}