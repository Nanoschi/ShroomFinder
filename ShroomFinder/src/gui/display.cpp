#pragma once
#include "SDL_image.h"

#include "../paths.h"
#include "display.h"

#include "../errors/error.h"
#include "gui_config.h"

Display::Display() {
	renderer = nullptr;
	window = nullptr;
	_init();
}

auto Display::_init() -> void {
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow(
		WinTitle.data(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		DefaultWinWidth, DefaultWinHeight,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (window == nullptr) {
		reportError(ErrorType::WindowError);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		reportError(ErrorType::RendererError);
	}
}

auto Display::_loadData() -> void {
	map_texture = IMG_LoadTexture(renderer, (const char*)paths::MapPath.c_str());
}

auto Display::clearScreen() -> void {
	SDL_SetRenderDrawColor(renderer, ClearColor.r, ClearColor.g, ClearColor.b, ClearColor.a);
	SDL_RenderClear(renderer);
}

auto Display::presentFrame() -> void {
	SDL_RenderPresent(renderer);
}

auto Display::drawFrame() -> void {

}