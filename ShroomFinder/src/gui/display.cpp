#pragma once
#include "SDL_image.h"

#include "paths.h"
#include "gui/display.h"

#include "error.h"
#include "gui/gui_config.h"

Display::Display() : 
	renderer{ DefaultWinWidth, DefaultWinHeight, WinTitle },
	camera{ {0, 0}, 1 } {

	_loadData();
	const glm::vec2 map_size = { map.getMapWidth(), map.getMapHeight() };
	const glm::vec2 half_map_size = map_size / 2.0f;
	camera.pos = { 
		-half_map_size.x,
		half_map_size.y};
	camera.zoom = 0.25;
}

auto Display::drawFrame() -> void {
	renderer.clearScreen(0.4f, 0.1f, 0.2f);
	
	map.render(renderer, camera);

	renderer.presentScreen();
}

auto Display::moveCamera(glm::vec2 delta) -> void {
	camera.move(delta);
}

auto Display::zoomIn(glm::vec2 target) -> void {
	camera.zoomTowards(target, ZoomSpeed);
}

auto Display::zoomOut(glm::vec2 target) -> void {
	camera.zoomTowards(target, 1 / ZoomSpeed);
}

auto Display::_loadData() -> void {
	map.loadData();
}