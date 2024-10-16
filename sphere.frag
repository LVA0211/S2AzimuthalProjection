#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 fragNormal;
in vec3 fragPosition;

uniform vec3 camPos;

float rangetorange(float value,float minRange,float maxRange, float minTarget, float maxTarget){
	return minTarget + (value-minRange)*(maxTarget-minTarget)/(maxRange-minRange);
};

void main()
{
	vec3 lightDir = normalize(camPos - fragPosition);
	vec3 normalizedNormal = normalize(fragNormal);

	float diff = rangetorange(max(dot(normalizedNormal,lightDir),0.0),	0.0,1.0		,0.2,1.0);

	FragColor = vec4(vec3(1.0,1.0,1.0)*diff, 1.0);
}