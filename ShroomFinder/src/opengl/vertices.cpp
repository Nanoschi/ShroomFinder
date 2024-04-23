#include "opengl/vertices.h"

auto getTestTriangleVertices(std::array<glm::vec2, 3>* out_vertices) -> void {
	(*out_vertices)[0] = { -0.5, -0.5 };
	(*out_vertices)[1] = { 0.5, -0.5 };
	(*out_vertices)[2] = { 0, 0.5 };
}

auto getCircleVertices(std::array<glm::vec2, 3>* out_vertices) -> void {
	(*out_vertices)[0] = { -1.7, -1 };
	(*out_vertices)[1] = { 1.7, -1 };
	(*out_vertices)[2] = { 0, 2.05 };
}

auto getTextureQuadVertices(std::array<TextureVertex, 6>* out_vertices) -> void {
	(*out_vertices)[0] = { { -1, -1 }, {0, 1} };
	(*out_vertices)[1] = { { -1, 1}, {0, 0} };
	(*out_vertices)[2] = { { 1,  -1}, {1, 1} };

	(*out_vertices)[3] = { { 1, 1 }, {1, 0} };
	(*out_vertices)[4] = { { -1, 1}, {0, 0} };
	(*out_vertices)[5] = { { 1,  -1}, {1, 1} };
}