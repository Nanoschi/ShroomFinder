#pragma once
#include "SDL.h"

#include "app.h"

App::App() {
	running = true;
}

auto App::run() -> void {
	while (running) {
		_pollInput();	
		display.drawFrame();
	}
}

auto App::close() -> void {

}

auto App::_pollInput() -> void {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
	}
}