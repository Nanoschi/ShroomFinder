#pragma once
#include "gui/camera.h"

Camera::Camera(glm::vec2 pos, float zoom) {
	this->pos = pos;
	this->zoom = zoom;
}

Camera::Camera() {
	Camera({ 0, 0 }, 1);
}

auto Camera::worldToScreen(glm::vec2 world_ccords, int win_width, int win_height) -> glm::vec2 {
	glm::vec2 screen_center = { win_width / 2.0f, win_height / 2.0f };
	glm::vec2 offset_pos = world_ccords + pos;
	glm::vec2 zoomed_pos = offset_pos * zoom;
	return zoomed_pos;
}

auto Camera::move(glm::vec2 delta) -> void {
	pos += delta;
}