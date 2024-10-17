#version 330 core
//Positions/Coordinates
flat layout (points) in;
layout (points, max_vertices = 7) out;

in vec3 color[];

out vec3 geomColor;

uniform vec3 Up;
uniform vec3 Right;
uniform vec3 projPos;

const float PI = 3.14159265358979323846;
const float epsilon = 0.1;

const vec4 aspect = vec4(PI,PI*9/8,1,1);

uniform float scale= 1.f;


vec3 project(vec3 P,vec3 C){
	float dist = dot(P,C);
	vec3 dir = (C-P*dist)/sqrt(1-dist*dist);

	return vec3(dot(dir,Right),dot(dir,Up),acos(dist));
};


void main()
{
	vec3 projection = project(projPos,gl_in[0].gl_Position.xyz);
	//if(projection.z > PI-epsilon){return;}
	geomColor = color[0];
	gl_PointSize = 10.0;
	for (int i = -2;i<=2;i++){
		gl_Position = vec4(projection.xy*(projection.z+2*PI*i),0,1)/aspect * vec4(scale,scale,1,1);
		EmitVertex();
	}
	EndPrimitive();
}