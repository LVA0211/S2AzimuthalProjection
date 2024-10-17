#version 330 core

layout(location = 0) in vec2 position;  // Vertex position on the unit sphere
out vec2 fragPosition;

void main()
{
    // Pass the position directly to the next stage (geometry shader)
    gl_Position = vec4(position,0.0, 1.0);
    fragPosition = position;
}