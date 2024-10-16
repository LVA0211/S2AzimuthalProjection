#version 330 core

out vec4 FragColor;  // Output color of the fragment

const vec3 leftColor = vec3(0.176f, 0.541f, 0.275f);  // Line color (default green)
const vec3 rightColor = vec3(0.4,0.4,0.4);

uniform ivec2 viewportSize;

uniform float scale;

void main()
{
    if(gl_FragCoord.x/viewportSize.x < 0.5){
        FragColor = vec4(leftColor,1.0);
    } else {
        if (distance(gl_FragCoord.xy,vec2(0.75,0.5)*viewportSize)<0.25*viewportSize.x*scale){
            FragColor = vec4(vec3(0.9),1.0);
        } else {
            FragColor = vec4(rightColor,1.0);
        }
    }
}