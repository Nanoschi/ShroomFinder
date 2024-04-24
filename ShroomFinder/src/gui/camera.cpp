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
	pos += glm::vec2{ delta.x, -delta.y };
}

auto Camera::getNormalCamPos(Renderer& renderer) const -> glm::vec2 {
	const glm::ivec2 win_size_i = renderer.getWinSize();
	const glm::vec2 win_size_f = { win_size_i.x, win_size_i.y };
	const glm::vec2 normal_cam_pos = (pos / win_size_f) * 2.0f;
	return normal_cam_pos / zoom;
}