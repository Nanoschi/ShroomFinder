#pragma once

#define GLEW_STATIC
#include "GL/glew.h"

auto GLAPIENTRY openglDebugCallback(
	GLenum source, 
	GLenum type, 
	GLuint id, 
	GLenum severity, 
	GLsizei length,
	const GLchar* message,
	const void* userParam) -> void;