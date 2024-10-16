#include "Sphere.h"
#include <iostream>
#define M_PI 3.14159265358979323846

Sphere::Sphere(unsigned int latSegments, unsigned int lonSegments){
	Sphere::latSegments = latSegments;
	Sphere::lonSegments = lonSegments;

    Sphere::primitive = GL_TRIANGLES;
    Sphere::update_mode = GL_STATIC_DRAW;

    generateVerts();
    generateTris();
    createAOs();
}

Sphere::~Sphere() {};

void Sphere::generateVerts() {
    
    if (lonSegments < 3) {
        lonSegments = 3;
    }
    if (latSegments < 3) {
        latSegments = 3;
    }

    float deltaLat = M_PI / latSegments;
    float deltaLon = 2 * M_PI / lonSegments;

    float latitude;
    float longitude;

    //Append north pole
    vertices.push_back(0.f);
    vertices.push_back(1.f);
    vertices.push_back(0.f);

    for (int i = 1; i < latSegments; ++i) {
         // Latitude angle
        latitude = i * deltaLat;

        float xz = sinf(latitude);
        float y = cosf(latitude);

        for (int j = 0; j < lonSegments; ++j) {

            longitude = j * deltaLon;

            float x = xz * cosf(longitude);
            float z = xz * sinf(longitude);
            //Push vertex
            Sphere::vertices.push_back(x);
            Sphere::vertices.push_back(y);
            Sphere::vertices.push_back(z);
            
        }
    }
    //Apend south pole
    vertices.push_back(0.f);
    vertices.push_back(-1.f);
    vertices.push_back(0.f);
}

void Sphere::generateTris() {
    //Tris around north pole (0th index)
    for (int s = 0; s < lonSegments-1; s++) {
        indices.push_back(0);
        indices.push_back(s+1);
        indices.push_back(s+2);
    };
    //Tri that connects 0, the last vertex in the 1st layer, and the first vertex in 1st layer. 
    indices.push_back(0);
    indices.push_back(lonSegments);
    indices.push_back(1);


    for (int r = 1; r < latSegments-1; ++r) {
        //Generating triangles for the 2nd trough last-1 layer
        for (int s = 0; s < lonSegments-1; ++s) {
            GLuint first = lonSegments *(r-1) +s + 1;
            GLuint second = first + lonSegments;

            // Create two triangles for each quad (except for the poles)
            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(second + 1);

            indices.push_back(first);
            indices.push_back(first + 1);
            indices.push_back(second + 1);
        }
        //Tris that connect the last index to the first index in this layer.
        indices.push_back(lonSegments * r);
        indices.push_back(lonSegments*(r+1));
        indices.push_back(lonSegments*r + 1);

        indices.push_back(lonSegments * r);
        indices.push_back(lonSegments * (r - 1) + 1);
        indices.push_back(lonSegments * r + 1);
    }
    //Tris around south pole(last index)

    unsigned int lastIndex = vertices.size()/3 - 1;
    for (int s = 1; s < lonSegments; s++) {
        indices.push_back(lastIndex);
        indices.push_back(lastIndex-s);
        indices.push_back(lastIndex-s-1);
    };
    //Tri that connects 0, the last vertex in the 1st layer, and the first vertex in 1st layer. 
    indices.push_back(lastIndex);
    indices.push_back(lastIndex-lonSegments);
    indices.push_back(lastIndex-1);
}