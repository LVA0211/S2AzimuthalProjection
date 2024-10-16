#version 330 core
//Positions/Coordinates
layout (location = 0) in vec3 aPos;

// Outputs the color for the Fragment Shader
out vec3 color;

uniform vec3 Up;
uniform vec3 Right;
uniform vec3 projPos;

uniform int selectedIndex;

const vec3 normalColor = vec3(1.0,0.0,0.0);
const vec3 selectedColor = vec3(0.0,1.0,0.0);

const float PI = 3.14159265358979323846;
const vec4 aspect = vec4(PI,PI*9/8,1,1);

uniform float scale= 1.f;


vec4 project(vec3 P,vec3 C){
	float dist = dot(P,C);
	vec3 dir = (C-P*dist)/sqrt(1-dist*dist)*acos(dist);

	return vec4(dot(dir,Right),dot(dir,Up),0.,1.);
};


void main()
{

	gl_Position = project(projPos,aPos)/aspect * vec4(scale,scale,1,1);

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