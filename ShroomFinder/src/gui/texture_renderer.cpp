#pragma once
#include "gui/texture_renderer.h"
#include "paths.h"

auto TextureRenderer::init() -> void {
	_loadVertexData();
	_loadShaderProgram();
	_getUniformLocations();
}

auto TextureRenderer::renderBoundTexture() -> void {
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

auto TextureRenderer::setTexturePosition(glm::vec2 position) -> void {
	glUniform2f(texture_position_uniform, position.x, position.y);
}

auto TextureRenderer::setTextureScale(glm::vec2 scale) -> void {
	glUniform2f(texture_scale_uniform, scale.x, scale.y);
}

auto TextureRenderer::setTextureScale(float scale) -> void {
	glUniform2f(texture_scale_uniform, scale, scale);
}

auto TextureRenderer::setTextureZoom(float zoom) -> void {
	glUniform2f(texture_zoom_uniform, zoom, zoom);
}

auto TextureRenderer::getVAO() -> VertexArray {
	return texture_vao;
}

auto TextureRenderer::getVBO() -> VertexBuffer {
	return texture_vbo;
}

auto TextureRenderer::getShaderProgram() -> ShaderProgram {
	return texture_program;
}

auto TextureRenderer::getScaleUniform() -> GLint {
	return texture_scale_uniform;
}

auto TextureRenderer::getPosUniform() -> GLint {
	return texture_position_uniform;
}

auto TextureRenderer::getZoomUniform() -> GLint {
	return texture_zoom_uniform;
}

auto TextureRenderer::_getUniformLocations() -> void {
	texture_scale_uniform = glGetUniformLocation(texture_program.getProgramId(), "u_scale");
	texture_position_uniform = glGetUniformLocation(texture_program.getProgramId(), "u_position");
	texture_zoom_uniform = glGetUniformLocation(texture_program.getProgramId(), "u_zoom");
}

auto TextureRenderer::_loadShaderProgram() -> void {
	texture_program.createProgram();
	texture_program.loadShadersFromFile(paths::TextureVertexShader, paths::TextureFragmentShader);
}

auto TextureRenderer::_loadVertexData() -> void {
	std::array<TextureVertex, 6> vertices;
	getTextureQuadVertices(&vertices);

	texture_vao.createVertexArray();
	texture_vao.bind();

	texture_vbo.createBuffer();
	texture_vbo.bind();
	texture_vbo.loadData(sizeof(vertices), (char*)&vertices);

	texture_vao.addAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), offsetof(TextureVertex, position));
	texture_vao.addAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), offsetof(TextureVertex, uv));
}
