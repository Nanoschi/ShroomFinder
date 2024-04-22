#pragma once
#include <string>

#define GLEW_STATIC
#include "GL/glew.h"

class ShaderProgram {
	GLuint program_id;
public:
	ShaderProgram();

	auto createProgram() -> void;

	auto use() -> void;

	auto unuse() -> void;

	auto destroy() -> void;

	auto getProgramId() -> GLuint;

	auto loadShadersFromFile(const std::string& vertex_path, const std::string& fragment_path) -> void;

	auto loadShadersFromSource(const std::string& vertex_path, const std::string& fragment_path) -> void;


private:
	auto _loadShader(const std::string& shader_source, GLenum shader_type) -> void;

	auto _checkShaderError(GLuint shader) -> void;
};