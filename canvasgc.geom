#version 330 core

const float PI = 3.14159265358979323846;

layout(lines) in;                       // Input is a line (2 vertices)
layout(line_strip, max_vertices = 100) out;  // Output as a line strip (great circle)

uniform int numSegments = 50;  // Number of points to subdivide the great circle
uniform mat4 camMatrix;    // Cam matrix to project points to screen

// Function to interpolate along the great circle
vec3 slerp(vec3 start, vec3 end, float t,float angle)
{
    // Normalize the start and end points (just in case)
    vec3 u = normalize(start);
    vec3 v = normalize(end);
    
    // Spherical linear interpolation (slerp)
    if (angle < 0.00001){return u;}; //AVOID DIVISION BY ZERO (sin(0)=0)

    if(angle > PI-0.0001){ //AVOID DIVISION BY ZERO (sin(180)=0)
        return (1.0-t)*start + t*end;
    }

    return (sin((1.0 - t) * angle) * u + sin(t * angle) * v) / sin(angle);
}

void main()
{
    vec3 p0 = gl_in[0].gl_Position.xyz;  // First vertex of the line
    vec3 p1 = gl_in[1].gl_Position.xyz;  // Second vertex of the line

    float omega = acos(dot(p0,p1));

    // Loop through and generate vertices along the great circle
    for (int i = 0; i <= numSegments; i++)
    {
        float t = float(i) / float(numSegments);// * ( 2*PI/omega );  // Interpolation factor (0 to 1)
        
        // Interpolate along the great circle
        vec3 pointOnCircle = slerp(p0, p1, t, omega);
        
        // Project the point and send it to the rasterizer
        gl_Position = camMatrix * vec4(pointOnCircle*1.01, 1.0);
        EmitVertex();
    }
    EndPrimitive();
}