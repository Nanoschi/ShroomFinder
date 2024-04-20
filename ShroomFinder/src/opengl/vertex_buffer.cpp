#pragma once
#include "opengl/vertex_buffer.h"

VertexBuffer::VertexBuffer() {
	glGenBuffers(1, &buffer_id);
}

VertexBuffer::~VertexBuffer() {
	//destroy();
}

auto VertexBuffer::bind() -> void {
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
}

auto VertexBuffer::unbind() -> void {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

auto VertexBuffer::destroy() -> void {
	glDeleteBuffers(1, &buffer_id);
}

auto VertexBuffer::getBufferId() -> GLuint {
	return buffer_id;
}

auto VertexBuffer::loadData(GLsizei size, char* data, GLenum usage) -> void {
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}