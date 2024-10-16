#include "Camera.h"

Camera::Camera(unsigned int width, unsigned int height, glm::vec3 position, float FOVdeg, float nearPlane, float farPlane) {
	Camera::width = width;
	Camera::height = height;

	Position = glm::normalize(position);

	Camera::FOVdeg = FOVdeg;
	Camera::nearPlane = nearPlane;
	Camera::farPlane = farPlane;

	Camera::Right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), Position));
	Camera::Up = glm::normalize(glm::cross(Position,Right));
}

glm::mat4 Camera::GetViewMatrix(){
	return glm::lookAt(GetViewPoint(), glm::vec3(0), Up);
}

glm::mat4 Camera::GetProjectionMatrix() {
	return glm::perspective(glm::radians(FOVdeg), (float)width/(float)height, nearPlane, farPlane);
}

glm::vec3 Camera::GetViewPoint() {
	return Position * camRadius;
}

void Camera::SendMatrixAndPos(Shader& shader, const char* matrixUniform,const char* posUniform) {
	glm::mat4 view = GetViewMatrix();
	glm::mat4 proj = GetProjectionMatrix();

	glm::vec3 pos = GetViewPoint();

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, matrixUniform), 1, GL_FALSE, glm::value_ptr(proj * view));
	glUniform3f(glGetUniformLocation(shader.ID, posUniform),pos.x,pos.y,pos.z);
}

void Camera::SetSize(unsigned int width,unsigned int height) {
	Camera::width = width;
	Camera::height = height;
}


glm::vec3 Camera::GetUnitSphereIntersection(glm::vec3 camPos, int mouseX,int mouseY) {
	glm::vec3 screenPos(mouseX, height - mouseY, 1.f);
	glm::vec4 viewport(0.0f, 0.0f, width, height);
	glm::vec3 dirRay = glm::unProject(screenPos, GetViewMatrix(), GetProjectionMatrix(), viewport) - GetViewPoint();

	float a = glm::dot(dirRay, dirRay); //len*len
	float b = 2.f * glm::dot(camPos, dirRay);
	float c = glm::dot(camPos, camPos) - 1.f;//len*len

	float D = b * b - 4.f * a * c;

	if (D >= 0) {
		float t1 = (-b - sqrt(D)) / (2.0f * a);
		float t2 = (-b + sqrt(D)) / (2.0f * a);

		float t = (t1 < t2) ? t1 : t2;

		return camPos + t * dirRay;
	}

	return glm::vec3(0, 0, 0);
}


void Camera::Inputs(GLFWwindow* window, CanvasShape& canvas, double delta)
{
	// Paralleltransport --> Rotate the point by a axis and update the other axis by rotating it too
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position = glm::rotate(Position, -SPEED * (float)delta, Right);
		Up = glm::rotate(Up, -SPEED * (float)delta, Right);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position = glm::rotate(Position, -SPEED * (float)delta, Up);
		Right = glm::rotate(Right, -SPEED * (float)delta, Up);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position = glm::rotate(Position, SPEED * (float)delta, Right);
		Up = glm::rotate(Up, SPEED * (float)delta, Right);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position = glm::rotate(Position, SPEED * (float)delta, Up);
		Right = glm::rotate(Right, SPEED * (float)delta, Up);
	}


	if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS) {
		canvas.DeleteSelected();
	}

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		currentZoom = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		currentZoom = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		currentZoom = 2;
	}

	//!MOUSE INPUTS
	glfwGetCursorPos(window, &mouseX, &mouseY);
	glm::vec3 result = GetUnitSphereIntersection(GetViewPoint(), mouseX, mouseY);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {

		if (dbRMB) {
			if (result != glm::vec3(0)) {
				if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				{
					canvas.ConnectSelectedAndNew(result);
				}
				else
				{
					canvas.AddAndSelectPoint(result);
				}
			}

			dbRMB = false;
		}
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
		dbRMB = true;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

		if (dbLMB) {
			if (result != glm::vec3(0)) {
				if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				{
					canvas.ConnectSelectedAndNearest(result);
				}
				else
				{
					canvas.SelectNearest(result);
				}
			}

			dbLMB = false;
		}
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		dbLMB = true;
	}

	if (!dbLMB) {
		if (result != glm::vec3(0)) {
			canvas.MoveSelected(result);
		}
	};
}

float Camera::zooms[3] = { 1.0f,0.5f,0.3333333334f };