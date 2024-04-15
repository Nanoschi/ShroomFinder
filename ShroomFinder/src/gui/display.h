#pragma once
#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "camera.h"

class Display {
public:
	SDL_Window* window;
	SDL_Renderer* renderer;

	Camera camera;

	SDL_Texture* map_texture;

	Display();

	auto clearScreen() -> void;

	auto presentFrame() -> void;

	auto drawFrame() -> void;

private:
	auto _init() -> void;

	auto _loadData() -> void;
};