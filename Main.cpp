#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"
#include"Game.h"

#include "ShapeIncluder.h"

int windowHeight = 720;
int windowWidth = 1280;

Camera camera(windowWidth/2, windowHeight, glm::vec3(0.f, 0.f, 1.f), 20.f, 0.1f, 100.f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// Set the viewport to match the new window size
	camera.SetSize(width/2,height);
	windowWidth = width;
	windowHeight = height;
}



int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "This is a window", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
	//Load GLAD so it configures OpenGL
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800

	glfwSetWindowAspectRatio(window,16,9);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader sphereProgram("sphere.vert", "sphere.frag");
	Shader canvasPointProgram("canvas.vert", "canvas.frag");
	Shader canvasLinesProgram("canvasgc.vert", "canvasgc.frag", "canvasgc.geom");

	Shader projPointProgram("canvasproj.vert", "canvasproj.frag","canvasproj.geom");
	Shader projLinesProgram("canvasprojgc.vert", "canvasprojgc.frag", "canvasprojgc.geom");

	Shader backgroundProgram("bg.vert", "bg.frag");

	//Enables settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_PROGRAM_POINT_SIZE);

	glLineWidth(2.0f);

	//BACKGROUND QUAD
	static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f,
	 1.0f, -1.0f,
	-1.0f,  1.0f,
	 1.0f,  1.0f
	};
	static const GLuint g_element_buffer_data[] = {0,1,3,0,2,3};

	VBO bgvbo;
	EBO bgebo;
	VAO bgvao;
	bgvao.Bind();
	bgvbo.Bind();
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(float), g_vertex_buffer_data, GL_STATIC_DRAW);
	bgebo.Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(int), g_element_buffer_data, GL_STATIC_DRAW);
	bgvao.LinkAttrib(bgvbo, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
	bgvao.Unbind();
	bgvbo.Unbind();
	bgebo.Unbind();


	Sphere sphere(20, 40);

	CanvasShape canvas;

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.176f, 0.541f, 0.275f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Game::updateDT();
		camera.Inputs(window, canvas, Game::dt);

		glViewport(0, 0, windowWidth, windowHeight);

		backgroundProgram.Activate();
		glUniform2i(glGetUniformLocation(backgroundProgram.ID, "viewportSize"),windowWidth,windowHeight);
		glUniform1f(glGetUniformLocation(backgroundProgram.ID, "scale"),Camera::zooms[camera.currentZoom]);
		bgvao.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
		bgvao.Unbind();
		glClear(GL_DEPTH_BUFFER_BIT);


		glViewport(0, 0, windowWidth / 2, windowHeight);

		//! DRAW SPHERE
		sphereProgram.Activate();
		camera.SendMatrixAndPos(sphereProgram, "camMatrix","camPos");

		sphere.draw();

		//! DRAW CANVAS
		canvasPointProgram.Activate();
		camera.SendMatrixAndPos(canvasPointProgram, "camMatrix", "camPos");
		glUniform1i(glGetUniformLocation(canvasPointProgram.ID, "selectedIndex"), canvas.selectedPointIndex);
		canvas.drawPoints();

		canvasLinesProgram.Activate();
		camera.SendMatrixAndPos(canvasLinesProgram, "camMatrix", "camPos");
		canvas.draw();


		//!RIGHT HALF
		glViewport(windowWidth / 2, 0,windowWidth/2, windowHeight);
		
		projPointProgram.Activate();
		glUniform3f(glGetUniformLocation(projPointProgram.ID,"projPos"),camera.Position.x,camera.Position.y,camera.Position.z);
		glUniform3f(glGetUniformLocation(projPointProgram.ID, "Up"), camera.Up.x, camera.Up.y, camera.Up.z);
		glUniform3f(glGetUniformLocation(projPointProgram.ID, "Right"), camera.Right.x, camera.Right.y, camera.Right.z);
		glUniform1i(glGetUniformLocation(projPointProgram.ID, "selectedIndex"), canvas.selectedPointIndex);

		glUniform1f(glGetUniformLocation(projPointProgram.ID, "scale"), Camera::zooms[camera.currentZoom]);
		canvas.drawPoints();

		projLinesProgram.Activate();
		glUniform3f(glGetUniformLocation(projLinesProgram.ID, "projPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		glUniform3f(glGetUniformLocation(projLinesProgram.ID, "Up"), camera.Up.x, camera.Up.y, camera.Up.z);
		glUniform3f(glGetUniformLocation(projLinesProgram.ID, "Right"), camera.Right.x, camera.Right.y, camera.Right.z);

		glUniform1f(glGetUniformLocation(projLinesProgram.ID, "scale"), Camera::zooms[camera.currentZoom]);
		canvas.draw();

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	sphereProgram.Delete();
	canvasPointProgram.Delete();
	canvasLinesProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}