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
}

auto Display::drawFrame() -> void {
	renderer.clearScreen(0.4f, 0.1f, 0.2f);
	
	map.render(renderer, camera);

	renderer.presentScreen();
}

auto Display::moveCamera(glm::vec2 delta) -> void {
	camera.move(delta);
}

auto Display::zoomIn() -> void {
	camera.zoom *= ZoomSpeed;
}

auto Display::zoomOut() -> void {
	camera.zoom /= ZoomSpeed;
}

auto Display::_loadData() -> void {
	map.loadData();
}