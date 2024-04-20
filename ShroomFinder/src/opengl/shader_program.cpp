#include <iostream>
#include "opengl/shader_program.h"
#include "load_file.h"

ShaderProgram::ShaderProgram() {
	program_id = glCreateProgram();
}

auto ShaderProgram::use() -> void {
	glUseProgram(program_id);
}

auto ShaderProgram::unuse() -> void {
	glUseProgram(0);
}

auto ShaderProgram::destroy() -> void {
	glDeleteProgram(program_id);
}

auto ShaderProgram::loadShadersFromFile(const std::string& vertex_path, const std::string& fragment_path) -> void {
	const std::string vertex_source = loadTextFile(vertex_path);
	const std::string fragment_source = loadTextFile(fragment_path);
	loadShadersFromSource(vertex_source, fragment_source);
}

auto ShaderProgram::loadShadersFromSource(const std::string& vertex_source, const std::string& fragment_source) -> void {
	_loadShader(vertex_source, GL_VERTEX_SHADER);
	_loadShader(fragment_source, GL_FRAGMENT_SHADER);
	glLinkProgram(program_id);
}

auto ShaderProgram::_loadShader(const std::string& shader_source, GLenum shader_type) -> void {
	GLuint shader = glCreateShader(shader_type);
	const char* c_src = shader_source.c_str();
	glShaderSource(shader, 1, &c_src, NULL);
	glCompileShader(shader);
	_checkShaderError(shader);
	glAttachShader(program_id, shader);
	//glDeleteShader(shader);
}

auto ShaderProgram::_checkShaderError(GLuint shader) -> void {
	GLint compile_status = 0; 
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

	if (compile_status == GL_FALSE) {
		GLint info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::string info_log;
		info_log.resize(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, (GLchar*)info_log.c_str());
		std::cerr << "[Shader Error]: ";
		std::cerr << info_log;
		std::cerr << std::endl;
	}
}
