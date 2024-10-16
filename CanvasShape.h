#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "Shape.h"

class CanvasShape : public Shape {
private:
	int GetLine(int index1, int index2); //Returns the "index" of the first index of the line connecting A and B (-1 if the line doesnt exitt)
	//Adds the provided vec3 to vertices and returns its index.
	int AddPoint(glm::vec3 point);
	void DeletePoint(int index);

	void ConnectPoints(int index1, int index2);

	void DeleteAllConnections(int index);

	GLint GetNearest(glm::vec3 point);
public:
	CanvasShape();

	GLint selectedPointIndex = -1;

	void Clear();

	void AddAndSelectPoint(glm::vec3 point);

	void DeleteSelected();

	void ConnectSelectedAndNearest(glm::vec3 pos);
	void ConnectSelectedAndNew(glm::vec3 point);

	void SeverPoints(unsigned int index1, unsigned int index2);
	
	void draw();

	void SelectNearest(glm::vec3 point);
	void MoveSelected(glm::vec3 newPos);
};