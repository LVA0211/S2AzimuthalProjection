#version 330 core

const float PI = 3.14159265358979323846;

layout(lines) in;                       // Input is a line (2 vertices)
layout(line_strip, max_vertices = 256) out;  // Output as a line strip (great circle)

uniform int numSegments = 50;  // Number of points to subdivide the great circle

uniform vec3 Up;
uniform vec3 Right;
uniform vec3 projPos;
uniform float scale;

const vec4 aspect = vec4(PI,PI*9/8,1,1);

const int depth = 5; //max = 6

const int totalverts = int(pow(2,(depth+1)))+1;

vec3 projections[totalverts];
float tvalues[totalverts];
int pointer;

// Function to interpolate along the great circle
vec3 slerp(vec3 start, vec3 end, float t,float angle)
{
    // Normalize the start and end points (just in case)
    vec3 u = normalize(start);
    vec3 v = normalize(end);
    
    // Spherical linear interpolation (slerp)
    //if (angle < 0.00001){return u;}; //AVOID DIVISION BY ZERO (sin(0)=0)

    return (sin((1.0 - t) * angle) * u + sin(t * angle) * v) / sin(angle);
}

vec3 project(/*vec3 P,*/vec3 C){
	float dist = dot(projPos,C);
	vec3 dir = (C-projPos*dist)/sqrt(1-dist*dist);

	return vec3(dot(dir,Right),dot(dir,Up),acos(dist));
};

vec4 projectiontogl_position(vec3 projection){
    return vec4(projection.xy*(projection.z)*scale,0,1)/aspect;
};


/*void recursiveSubdivide(vec3 p0, float t0, vec3 p1, float t1, int depth){
    if(depth>5){return;}


    vec3 p0_ = project(p0);
    vec3 p1_ = project(p1);

    float lerpval = p0_.z/(p0_.z+p1_.z);
    float tm = t0*lerpval+t1*(1-lerpval);

    vec3 pm = slerp(p0,p1,tm,acos(dot(p0,p1)));
    vec3 pm_ = project(pm);

    gl_Position = projectiontogl_position(p0_);
    EmitVertex();
    recursiveSubdivide(p0,t0,pm,tm,depth+1);
    gl_Position = projectiontogl_position(pm_);
    EmitVertex();
    recursiveSubdivide(pm,tm,p1,t1,depth+1);
    gl_Position = projectiontogl_position(p1_);
    EmitVertex();
};*/


void main()
{
    vec3 pstart = gl_in[0].gl_Position.xyz;  // First vertex of the line
    vec3 pend = gl_in[1].gl_Position.xyz;  // Second vertex of the line

    float omega = acos(dot(pstart,pend));

    vec3 pmid = slerp(pstart,pend,0.5,omega);

    projections[0] = project(pstart);
    tvalues[0] = 0.0;

    projections[totalverts-1] = project(pend);
    tvalues[totalverts-1] = 1.0;

    projections[(totalverts-1)/2] = project(pmid);
    tvalues[(totalverts-1)/2]=0.5;

    for(int level = 1;level<= depth;level++){
    int totalsegments = int(pow(2,level+1));
    int spacing = (totalverts-1)/totalsegments;

    for(int segment = 0;segment<totalsegments;segment++){
        int index0 = spacing*segment;
        int index1 = spacing*(segment+1);

        vec3 p0 = projections[index0];
        vec3 p1 = projections[index1];
        float t0 = tvalues[index0];
        float t1 = tvalues[index1];

        float lerpval = pow(p0.z/(p0.z+p1.z),1.5);
        float tnew = t0*lerpval+t1*(1-lerpval);

        vec3 pnew = project(slerp(pstart,pend,tnew,omega));

        int indexnew = (index0+index1)/2;

        projections[indexnew] = pnew;
        tvalues[indexnew] = tnew;
    }
    };

    //emit all points
    for(int i=0;i<totalverts;i++){
        gl_Position = projectiontogl_position(projections[i]);
        EmitVertex();
    };
    EndPrimitive();

    //float omega = acos(dot(p0,p1));

    // Loop through and generate vertices along the great circle
    /*for (int j = -2;j<=2;j++){

    for (int i = 0; i <= numSegments; i++)
    {
        float t = float(i) / float(numSegments);//* ( 2*PI/omega );  // Interpolation factor (0 to 1)
        
        // Interpolate along the great circle
        vec3 pointOnCircle = slerp(p0, p1, t, omega);
        
        vec3 projection = project(projPos,pointOnCircle);
        // Project the point and send it to the rasterizer
            gl_Position = vec4(projection.xy*(projection.z+2*PI*j),0,1)/aspect * vec4(scale,scale,1,1);
            EmitVertex();

    }
    EndPrimitive();
    }*/
    
}