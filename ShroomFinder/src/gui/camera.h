#pragma once
#include "vec2.hpp"

struct Camera {
	glm::vec2 pos;
	float zoom;

	Camera();

	Camera(glm::vec2 pos, float zoom);

	auto move(glm::vec2 delta) -> void;
};