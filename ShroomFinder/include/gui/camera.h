#pragma once
#include "vec2.hpp"
#include "gui/renderer.h"

struct Camera {
	glm::vec2 pos;
	float zoom;

	Camera();

	Camera(glm::vec2 pos, float zoom);

	auto move(glm::vec2 delta) -> void;

	auto worldToScreen(glm::vec2 world_ccords, int win_width, int win_height) -> glm::vec2;

	auto getNormalCamPos(Renderer& renderer) const -> glm::vec2;
};