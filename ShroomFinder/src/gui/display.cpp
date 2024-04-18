#pragma once
#include "SDL_image.h"

#include "../paths.h"
#include "display.h"

#include "../errors/error.h"
#include "gui_config.h"

Display::Display() : renderer{ DefaultWinWidth, DefaultWinHeight, WinTitle } {
	_loadData();
}

auto Display::_loadData() -> void {
	map_texture = IMG_LoadTexture(renderer.sdl_renderer, paths::MapPath.c_str());
	printf(SDL_GetError());

}

auto Display::drawFrame() -> void {
	renderer.clearScreen(255, 20, 20);
	renderer.renderTexture(map_texture, camera, 10, 10, 0.6);
	renderer.presentScreen();
}

auto Display::moveCamera(glm::vec2 delta) -> void {
	camera.move(delta);
}

auto Display::zoomCamera(float zoom_delta) -> void {
	camera.zoom += zoom_delta;
}

auto Display::zoomCameraTo(float zoom) -> void {
	camera.zoom = zoom;
}
