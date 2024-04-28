#pragma once
#include "vec2.hpp"
#include "gui/renderer.h"

struct Camera {
	glm::vec2 pos;
	float zoom;

	Camera();

	Camera(glm::vec2 pos, float zoom);

	auto move(glm::vec2 delta) -> void;

	auto getNormalCamPos(Renderer& renderer) const -> glm::vec2;

	auto WorldToScreen(glm::vec2 world_pos) -> glm::vec2;

	auto ScreenToWorld(glm::vec2 screen_pos) -> glm::vec2;

	auto RasterToScreen(glm::vec2 raster_pos, glm::vec2 win_size) -> glm::vec2;

	auto ScreenToRaster(glm::vec2 screen_pos, glm::vec2 win_size) -> glm::vec2;

	auto zoomTowards(glm::vec2 screen_target, float amount) -> void;

	auto zoomOutTowards(glm::vec2 screen_target, float amount) -> void;

};