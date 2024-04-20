#pragma once
#define GLEW_STATIC
#include "GL/glew.h"

class VertexBuffer {
	GLuint buffer_id;

public:
	VertexBuffer();

	~VertexBuffer();

	auto createBuffer() -> void;

	auto bind() -> void;

	auto unbind() -> void;

	auto destroy() -> void;

	auto loadData(GLsizei size, char* data, GLenum usage = GL_STATIC_DRAW) -> void;

	auto getBufferId() -> GLuint;
};