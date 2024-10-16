#pragma once

#include<vector>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "VAO.h"
#include "EBO.h"

class Shape {
protected:
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
public:
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    GLenum primitive;
    GLenum update_mode;

    VAO vao= VAO();
    VBO vbo = VBO();
    EBO ebo = EBO();

    virtual ~Shape();

    virtual void draw();
    virtual void drawPoints();

protected:
    void createAOs();
    
};