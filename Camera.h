#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"
#include"CanvasShape.h"

class Camera
{
private:
	const float SPEED = 2.f;
	const glm::vec3 GLOBALUP = glm::vec3(0, 1, 0);

	bool dbLMB = true;
	bool dbRMB = true;

	float camRadius = 10.f;

	unsigned int width, height;

	glm::vec3 m_OriginalPosition;

	void Reset();
public:
	glm::vec3 Position;
	glm::vec3 Up;
	glm::vec3 Right;
	
	unsigned short currentZoom = 0;
	static float zooms[3];

	float FOVdeg, nearPlane, farPlane;
	float sensitivity = 100.0f;
	// Stores the coordinates of the cursor
	double mouseX = 0.;
	double mouseY = 0.;

	bool firstClick = true;

	// Camera constructor to set up initial values
	Camera(unsigned int width, unsigned int height, glm::vec3 position, float FOVdeg, float nearPlane, float farPlane);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	glm::vec3 GetViewPoint();

	glm::vec3 GetUnitSphereIntersection(glm::vec3 camPos, int mouseX, int mouseY);

	void SetSize(unsigned int width, unsigned int height);

	void SendMatrixAndPos(Shader& shader, const char* matrixUniform, const char* posUniform);

	void Inputs(GLFWwindow* window,CanvasShape& canvas, double delta);
};

#endif
