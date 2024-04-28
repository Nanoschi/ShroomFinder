#pragma once
#include "gui/camera.h"

Camera::Camera(glm::vec2 pos, float zoom) {
	this->pos = pos;
	this->zoom = zoom;
}

Camera::Camera() {
	Camera({ 0, 0 }, 1);
}

auto Camera::move(glm::vec2 delta) -> void {
	pos += glm::vec2{ delta.x, delta.y };
}

auto Camera::getNormalCamPos(Renderer& renderer) const -> glm::vec2 {
	const glm::ivec2 win_size_i = renderer.getWinSize();
	const glm::vec2 win_size_f = { win_size_i.x, win_size_i.y };
	const glm::vec2 normal_cam_pos = (pos / win_size_f) * 2.0f;
	return normal_cam_pos / zoom;
}

auto Camera::WorldToScreen(glm::vec2 world_pos) -> glm::vec2 {
	return (world_pos + pos) * zoom;
}

auto Camera::ScreenToWorld(glm::vec2 screen_pos) -> glm::vec2 {
	return (screen_pos / zoom) - pos;
}

auto Camera::RasterToScreen(glm::vec2 raster_pos, glm::vec2 win_size) -> glm::vec2 {
	const glm::vec2 half_win_size = win_size / 2.0f;
	const glm::vec2 centered_raster = raster_pos - half_win_size;
	const glm::vec2 normal_raster = centered_raster / half_win_size;
	return glm::vec2(normal_raster.x, -normal_raster.y);
}

auto Camera::ScreenToRaster(glm::vec2 screen_pos, glm::vec2 win_size) -> glm::vec2 {
	const glm::vec2 flipped_screen_pos = glm::vec2(screen_pos.x, -screen_pos.y);
	const glm::vec2 positive_screen_pos = screen_pos + glm::vec2{1.0f, 1.0f};
	const glm::vec2 raster_pos = positive_screen_pos * (win_size / 2.0f);
	return raster_pos;
}

auto Camera::zoomTowards(glm::vec2 screen_target, float amount) -> void {
	/*const glm::vec2 world_target_current = ScreenToWorld(screen_target);
	zoom *= amount;
	const glm::vec2 world_target_after = ScreenToWorld(screen_target);
	const glm::vec2 world_delta = world_target_after - world_target_current;
	const glm::vec2 screen_delta = world_delta / (zoom / amount);
	pos += screen_delta;*/
	zoom *= amount;
}