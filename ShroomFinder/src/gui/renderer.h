#pragma once
#include <utility>
#include <string>

#include "SDL.h"

class Renderer {
public:
	SDL_Renderer* sdl_renderer;
	SDL_Window* sdl_window;

	Renderer(int win_width, int win_height, const std::string& title);

	auto clearScreen(uint8_t r, uint8_t g, uint8_t b) -> void;

	auto presentScreen() -> void;

	auto renderTexture(SDL_Texture* texture, int x, int y, float scale = 1.0f) -> void;

	auto getWinSize() -> std::pair<int, int>;
};