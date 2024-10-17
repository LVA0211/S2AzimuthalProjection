#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 geomColor;


void main()
{
	vec2 coord = gl_PointCoord-vec2(0.5);

	if (length(coord)>0.5) discard;

	FragColor = vec4(geomColor, 1.0);
}