#pragma once
#include "opengl/texture.h"

Texture::Texture() {
	texture_id = 0;
}

auto Texture::createTexture() -> void {
	glGenTextures(1, &texture_id);
	bind();
	_configureTexture();
	unbind();
}

auto Texture::bind() -> void {
	glBindTexture(GL_TEXTURE_2D, texture_id);
}

auto Texture::unbind() -> void {
	glBindTexture(GL_TEXTURE_2D, 0);
}

auto Texture::destroy() -> void {
	glDeleteTextures(1, &texture_id);
	texture_id = 0;
}

auto Texture::hasData() -> bool {
	return texture_id != 0;
}

auto Texture::getSize() -> glm::ivec2 {
	return { width, height };
}

auto Texture::getAspect() -> float {
	return (float)width / height;
}

auto Texture::loadTextureFromMemory(char* data, int width, int height) -> void {
	this->width = width;
	this->height = height;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA_BPTC_UNORM, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
}

auto Texture::_configureTexture() -> void {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
}