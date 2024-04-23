#pragma once
#define GLEW_STATIC
#include "GL/glew.h"

#include "vec2.hpp"

class Texture {
	GLuint texture_id;
	int width, height;

public:
	Texture();

	auto createTexture() -> void;

	auto bind() -> void;

	auto unbind() -> void;

	auto destroy() -> void;

	auto loadTextureFromMemory(char* data, int width, int height) -> void;

	auto hasData() -> bool;

	auto getSize() -> glm::ivec2;

	auto getAspect() -> float;

private:
	auto _configureTexture() -> void;
};