#include "CanvasShape.h"
#include <iostream>

CanvasShape::CanvasShape(){
	primitive = GL_LINES;
	update_mode = GL_DYNAMIC_DRAW;

	modelMatrix = glm::scale(modelMatrix, glm::vec3(1.1f));
	//!TEMPORARY
	vertices = { 0.f,1.f,0.f,0.f,-1.f,0.f};

	createAOs();
};

void CanvasShape::Clear() {
	vertices = {};
	indices = {};
};


int CanvasShape::AddPoint(glm::vec3 point) {
	vertices.push_back(point.x);
	vertices.push_back(point.y);
	vertices.push_back(point.z);

	vbo.Bind();
	vbo.UpdateData(vertices, vertices.size() * sizeof(float), update_mode);
	vbo.Unbind();

	return vertices.size() / 3 - 1;
}

void CanvasShape::DeletePoint(int index) {
	vertices.erase(vertices.begin() + index * 3, vertices.begin() + index * 3 + 3);
	//Fix all the indices
	for (int i = 0; i < indices.size(); i++) {
		if (indices[i] > index) {
			indices[i]--;
		}
	}
}

void CanvasShape::ConnectPoints(int index1, int index2) {
	if (GetLine(index1,index2) == -1) {
		indices.push_back(index1);
		indices.push_back(index2);
		std::cout << "Connected points!" << std::endl;
	}
};

void CanvasShape::DeleteAllConnections(int index) {
	for (int i = 0; i < indices.size() / 2; i++) {
		if (index == indices[i * 2] || index == indices[i * 2 + 1]) {
			indices.erase(indices.begin() + i * 2, indices.begin() + i * 2 + 2);
		}
	}
}

int CanvasShape::GetLine(int index1, int index2) {
	for (int i = 0; i < indices.size() / 2; i++) {
		if (index1 == indices[i*2] && index2 == indices[i*2 + 1] || index1 == indices[i*2+1] && index2 == indices[i*2]) {
			return i * 2;
		}
	}
	return -1;
}

GLint CanvasShape::GetNearest(glm::vec3 point) {
	float currentClosestDistance2 = FLT_MAX;
	GLuint currentClosestPoint = 0;
	for (int i = 0; i < vertices.size() / 3; i++) {
		float xdif = (point.x - vertices[i * 3]);
		float ydif = (point.y - vertices[i * 3 + 1]);
		float zdif = (point.z - vertices[i * 3 + 2]);
		float dist2 = xdif * xdif + ydif * ydif + zdif * zdif;

		if (dist2 < currentClosestDistance2) {
			currentClosestDistance2 = dist2;
			currentClosestPoint = i;
		}
	}

	if (currentClosestDistance2 > 0.005)
	{
		return -1;
	}
	else
	{
		return currentClosestPoint;
	}
}

//!PUBLIC METHODS

void CanvasShape::AddAndSelectPoint(glm::vec3 point) {
	selectedPointIndex = AddPoint(point);
}

void CanvasShape::DeleteSelected() {
	if (selectedPointIndex<2) return;

	DeleteAllConnections(selectedPointIndex);
	DeletePoint(selectedPointIndex);

	selectedPointIndex = -1;

	vbo.Bind();
	vbo.UpdateData(vertices, vertices.size() * sizeof(float), update_mode);
	vbo.Unbind();
}

void CanvasShape::ConnectSelectedAndNearest(glm::vec3 pos) {
	GLint newselected = GetNearest(pos);

	if (newselected == -1) {
		selectedPointIndex = -1;
		return;
	}
	if(selectedPointIndex == -1 || newselected == selectedPointIndex) return;

	ConnectPoints(newselected, selectedPointIndex);
	
	ebo.Bind();
	ebo.UpdateData(indices, indices.size() * sizeof(GLuint), update_mode);
	ebo.Unbind();

	selectedPointIndex = newselected;
}

void CanvasShape::ConnectSelectedAndNew(glm::vec3 point) {
	if (selectedPointIndex == -1) return;

	int index = AddPoint(point);

	ConnectPoints(index, selectedPointIndex);

	ebo.Bind();
	ebo.UpdateData(indices, indices.size() * sizeof(GLuint), update_mode);
	ebo.Unbind();

	selectedPointIndex = index;
}

void CanvasShape::SeverPoints(unsigned int index1, unsigned int index2) {

}

void CanvasShape::SelectNearest(glm::vec3 point) {
	selectedPointIndex = GetNearest(point);
}

void CanvasShape::MoveSelected(glm::vec3 newPos) {
	if (selectedPointIndex <2) return;

	vertices[selectedPointIndex * 3] = newPos.x;
	vertices[selectedPointIndex * 3 + 1] = newPos.y;
	vertices[selectedPointIndex * 3 + 2] = newPos.z;

	vbo.Bind();
	vbo.UpdateData(vertices, vertices.size() * sizeof(float), update_mode);
	vbo.Unbind();
}

void CanvasShape::draw() {
	vao.Bind();
	glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, (void*)0);
	vao.Unbind();
};