#pragma once
#include "opengl/index_buffer.h"

IndexBuffer::IndexBuffer() {
	buffer_id = 0;
}
IndexBuffer::~IndexBuffer() {
	//destroy();
}

auto IndexBuffer::createBuffer() -> void {
	glGenBuffers(1, &buffer_id);
}

auto IndexBuffer::bind() -> void {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
}

auto IndexBuffer::unbind() -> void {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

auto IndexBuffer::destroy() -> void {
	glDeleteBuffers(1, &buffer_id);
}

auto IndexBuffer::getBufferId() -> GLuint {
	return buffer_id;
}

auto IndexBuffer::loadData(GLsizei size, char* data, GLenum usage) -> void {
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}