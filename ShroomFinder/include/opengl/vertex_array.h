#pragma once
#define GLEW_STATIC
#include "GL/glew.h"

class VertexArray {
	GLuint vao_id;

public:
	VertexArray();

	~VertexArray();

	auto createVertexArray() -> void;

	auto bind() -> void;

	auto unbind() -> void;

	auto destroy() -> void;

	auto addAttribPointer(GLuint index, GLint element_count, GLenum type, GLboolean normalize, GLsizei stride, GLsizei offset) -> void;

	auto getVertexArrayId() -> GLuint;
};