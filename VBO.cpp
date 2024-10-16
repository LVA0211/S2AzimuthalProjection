#include"VBO.h"


VBO::VBO() {
	glGenBuffers(1, &ID);
};


void VBO::UpdateData(std::vector<GLfloat>& vertices, GLsizeiptr size,GLenum update_mode)
{
	glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), update_mode);
}

// Binds the VBO
void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbinds the VBO
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}