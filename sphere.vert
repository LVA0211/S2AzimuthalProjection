#version 330 core

//Positions/Coordinates
layout (location = 0) in vec3 aPos;

// Outputs the color for the Fragment Shader
out vec3 fragNormal;
out vec3 fragPosition;

uniform mat4 camMatrix;




void main()
{
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix*vec4(aPos,1.0);

	fragPosition = aPos;
	fragNormal = aPos;
}