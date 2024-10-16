#include "Shape.h";
#include <iostream>



void Shape::createAOs() {
    vao.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    vbo.Bind();
    vbo.UpdateData(vertices, vertices.size()*sizeof(float),update_mode);
    // Generates Element Buffer Object and links it to indices
    ebo.Bind();
    ebo.UpdateData(indices, indices.size()*sizeof(int),update_mode);

    // Links VBO attributes such as coordinates and normals to VAO
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    //xvao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}

Shape::~Shape() {
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
}

void Shape::draw(){
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
    //glDrawArrays(GL_POINTS, 0, vertices.size()/6);
    vao.Unbind();
}

void Shape::drawPoints() {
    vao.Bind();
    glDrawArrays(GL_POINTS, 0, vertices.size() / 3);
    vao.Unbind();
}