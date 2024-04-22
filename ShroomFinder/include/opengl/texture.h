#pragma once
#define GLEW_STATIC
#include "GL/glew.h"

class Texture {
	GLuint texture_id;

public:
	Texture();

	auto createTexture() -> void;

	auto bind() -> void;

	auto unbind() -> void;

	auto destroy() -> void;

	auto loadDataFromMemory(char* data, int width, int height) -> void;

private:
	auto _configureTexture() -> void;
};