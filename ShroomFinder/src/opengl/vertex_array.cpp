#include "opengl/vertex_array.h"

VertexArray::VertexArray() {
	vao_id = 0;
}

VertexArray::~VertexArray() {
	//vao_id = 0;
}

auto VertexArray::createVertexArray() -> void {
	glGenVertexArrays(1, &vao_id);
}

auto VertexArray::bind() -> void {
	glBindVertexArray(vao_id);
}

auto VertexArray::unbind() -> void {
	glBindVertexArray(0);
}

auto VertexArray::destroy() -> void {
	glDeleteVertexArrays(1, &vao_id);
	vao_id = 0;
}

auto VertexArray::addAttribPointer(GLuint index, GLint element_count, GLenum type, GLboolean normalize, GLsizei stride, GLsizei offset) -> void {
	glVertexAttribPointer(index, element_count, type, normalize, stride, (void*)offset);
	glEnableVertexAttribArray(index);
}

auto VertexArray::getVertexArrayId() -> GLuint {
	return vao_id;
}