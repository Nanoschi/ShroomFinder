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