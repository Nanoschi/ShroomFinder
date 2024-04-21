#pragma once
#include <array>
#include "vec2.hpp"

struct TextureVertex {
	glm::vec2 position;
	glm::vec2 uv;
};

auto getTestTriangleVertices(std::array<glm::vec2, 3>* out_vertices) -> void;

auto getCircleVertices(std::array<glm::vec2, 3>* out_vertices) -> void;

auto getTextureQuadVertices(std::array<TextureVertex, 3>* out_vertices) -> void;