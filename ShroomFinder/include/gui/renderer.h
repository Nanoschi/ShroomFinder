#pragma once
#include <utility>
#include <string>

#include "SDL.h"
#include "vec2.hpp"

#include "gui/texture_renderer.h"

class Renderer {
public:
	SDL_Renderer* sdl_renderer;
	SDL_Window* sdl_window;
	SDL_GLContext gl_context;

	TextureRenderer texture_renderer;

	Renderer(int win_width, int win_height, const std::string& title);

	auto clearScreen(GLclampf r, GLclampf g, GLclampf b) -> void;

	auto presentScreen() -> void;

	auto getWinSize() -> glm::ivec2;

private:
	auto _initGraphicsSystem(int win_width, int win_height, const std::string& title) -> void;
};