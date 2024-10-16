#include"EBO.h"


EBO::EBO(){
	glGenBuffers(1, &ID);
}

// Constructor that generates a Elements Buffer Object and links it to indices

void EBO::UpdateData(std::vector<GLuint>& indices, GLsizeiptr size, GLenum update_mode) {
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices.data(), update_mode);
}

// Binds the EBO
void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbinds the EBO
void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the EBO
//task tes
void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}