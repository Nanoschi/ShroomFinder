#pragma once
#define GLEW_STATIC
#include "GL/glew.h"

class IndexBuffer {
	GLuint buffer_id;

public:
	IndexBuffer();

	~IndexBuffer();

	auto createBuffer() -> void;

	auto bind() -> void;

	auto unbind() -> void;

	auto destroy() -> void;

	auto loadData(GLsizei size, char* data, GLenum usage = GL_STATIC_DRAW) -> void;

	auto getBufferId() -> GLuint;
};