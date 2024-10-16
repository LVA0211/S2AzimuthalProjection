#version 330 core

layout(location = 0) in vec3 position;  // Vertex position on the unit sphere

void main()
{
    // Pass the position directly to the next stage (geometry shader)
    gl_Position = vec4(position, 1.0);
}