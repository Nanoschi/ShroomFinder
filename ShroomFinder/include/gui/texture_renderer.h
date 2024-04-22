#pragma once
#include "opengl/texture.h"
#include "opengl/vertex_buffer.h"
#include "opengl/vertex_array.h"
#include "opengl/shader_program.h"
#include "opengl/vertices.h"

class TextureRenderer {
	VertexArray texture_vao;
	VertexBuffer texture_vbo;
	ShaderProgram texture_program;

	GLint texture_scale_uniform;
	GLint texture_position_uniform;

public:
	auto init() -> void;

	auto renderBoundTexture() -> void;

	auto setTexturePosition(glm::vec2 position) -> void;

	auto setTextureScale(glm::vec2 scale) -> void;

	auto setTextureScale(float scale) -> void;

	auto getVAO() -> VertexArray;

	auto getVBO() -> VertexBuffer;

	auto getShaderProgram() -> ShaderProgram;

	auto getScaleUniform() -> GLint;

	auto getPosUniform() -> GLint;

private:
	auto _getUniformLocations() -> void;

	auto _loadShaderProgram() -> void;

	auto _loadVertexData() -> void;
};