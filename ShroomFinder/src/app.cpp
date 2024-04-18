#pragma once
#include <algorithm>
#include "SDL.h"

#include "app.h"

App::App() {
	running = true;

	mouse_pos = { 0, 0 };
	delta_mouse_pos = { 0, 0 };
	scroll = 0;
}

auto App::run() -> void {
	while (running) {
		_pollInput();
		_tryMoveCamera();
		display.drawFrame();
	}
}

auto App::close() -> void {

}

auto App::_pollInput() -> void {
	SDL_Event event;
	scroll = 0;
	int mouse_x = 0;
	int mouse_y = 0;
	mouse_buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
	_updateMousePos(mouse_x, mouse_y);

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
		if (event.type == SDL_MOUSEWHEEL) {
			scroll = event.wheel.preciseY;
		}
		printf("%f\n", scroll);
	}
}

auto App::_updateMousePos(int mouse_x, int mouse_y) -> void {
	glm::vec2 new_mouse_pos = { mouse_x, mouse_y };
	delta_mouse_pos = mouse_pos - new_mouse_pos;
	mouse_pos = new_mouse_pos;
}

auto App::_tryMoveCamera() -> void {
	if (mouse_buttons & SDL_BUTTON_LMASK) {
		display.moveCamera(delta_mouse_pos);
	}
	display.zoomCamera(scroll * 0.01);
}
