#pragma once
#include "Shape.h"

class Sphere : public Shape {
public:
	Sphere(unsigned int latSegments, unsigned int lonSegments);
	~Sphere();
private:
	unsigned int latSegments;
	unsigned int lonSegments;

	void generateVerts();
	void generateTris();
};