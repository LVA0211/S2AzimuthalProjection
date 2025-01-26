#version 330 core

in vec2 fragPosition;

out vec4 FragColor;  // Output color of the fragment

const vec2 aspect = vec2(1.0,9.0/8.0);
const float PI = 3.14159265358979323846;

const vec3 meColor = vec3(0,0,1);
const vec3 antiMeColor = vec3(1,0,0);

uniform float scale;

void main()
{
	//float len = length(fragPosition*aspect)/scale;

	//float val_ = cos(PI*len);

	//float val = pow(val_,4)*val_;
	
	//if (val > 0){
		//FragColor = vec4(val*meColor + (1-val)*vec3(1),1);
	//} else {
		//FragColor = vec4(-val*antiMeColor + (1+val)*vec3(1),1);
	//}

	float len = length(fragPosition*aspect);

	float val = mod(len/scale,2.0);

	if(val<1){
	FragColor=vec4(1);
	} else {
	FragColor=vec4(0);
	}


}