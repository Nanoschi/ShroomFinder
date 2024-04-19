#include <iostream>
#include "opengl/debug.h"

auto GLAPIENTRY openglDebugCallback(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam) -> void {
	std::cerr << "[OpenGL Error]: ";
	std::cerr << "(Source: " << source;
	std::cerr << ", Id: " << id;
	std::cerr << ", Severity: " << severity;
	std::cerr << ") " << message;
	std::cerr << std::endl;
}