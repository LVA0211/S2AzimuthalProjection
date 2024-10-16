#version 330 core

//Positions/Coordinates
layout (location = 0) in vec3 aPos;

// Outputs the color for the Fragment Shader
out vec3 color;

uniform mat4 camMatrix;
uniform vec3 camPos;

uniform int selectedIndex;

const vec3 normalColor = vec3(1.0,0.0,0.0);
const vec3 selectedColor = vec3(0.0,1.0,0.0);

void main()
{
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix*vec4(1.01*aPos,1.0);

	gl_PointSize = 10.0;
	// Assigns the colors from the Vertex Data to "color"
	if(gl_VertexID == selectedIndex)
	{
		color = selectedColor;
	}
	else
	{
		color = normalColor;
	}
}