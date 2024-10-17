#version 330 core

out vec4 FragColor;  // Output color of the fragment

const vec3 lineColor = vec3(0.0, 0.0, 0.0);// Line color (default green)

void main()
{
    // Simple flat color for the great circles
    FragColor = vec4(lineColor, 1.0);
}