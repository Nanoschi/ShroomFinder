#pragma once
#include "opengl/texture.h"

Texture::Texture() {
	texture_id = 0;
}

auto Texture::createTexture() -> void {
	glGenTextures(1, &texture_id);
}

auto Texture::bind() -> void {
	glBindTexture(GL_TEXTURE_2D, texture_id);
}

auto Texture::unbind() -> void {
	glBindTexture(GL_TEXTURE_2D, 0);
}

auto Texture::destroy() -> void {
	glDeleteTextures(1, &texture_id);
}

auto Texture::loadDataFromBuffer(char* data, int width, int height) -> void {
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
}

auto Texture::_configureTexture() -> void {

}