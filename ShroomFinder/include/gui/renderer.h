#pragma once
#include <utility>
#include <string>

#include "SDL.h"

#include "camera.h"
#include "opengl/vertex_buffer.h"

class Renderer {
public:
	SDL_Renderer* sdl_renderer;
	SDL_Window* sdl_window;
	SDL_GLContext gl_context;

	//VertexBuffer texture_quad_vertices;

	Renderer(int win_width, int win_height, const std::string& title);

	auto clearScreen(GLclampf r, GLclampf g, GLclampf b) -> void;

	auto presentScreen() -> void;

	auto renderTexture(SDL_Texture* texture, const Camera& camera, int x, int y, float scale = 1.0f) -> void;

	auto getWinSize() -> std::pair<int, int>;

private:
	auto _initGraphicsSystem(int win_width, int win_height, const std::string& title) -> void;
};