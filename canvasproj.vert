#version 330 core
//Positions/Coordinates
layout (location = 0) in vec3 aPos;

// Outputs the color for the Fragment Shader
out vec3 color;

uniform int selectedIndex;

const vec3 normalColor = vec3(1.0,0.0,0.0);
const vec3 selectedColor = vec3(0.0,1.0,0.0);

void main()
{

	gl_Position = vec4(aPos,1.0);
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