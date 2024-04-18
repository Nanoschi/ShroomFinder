#include "SDL_image.h"
#include "renderer.h"
#include "../errors/error.h"

Renderer::Renderer(int win_width, int win_height, const std::string& title) {
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	sdl_window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		win_width, win_height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (sdl_window == nullptr) {
		reportError(ErrorType::WindowError);
	}

	sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);

	if (sdl_renderer == nullptr) {
		reportError(ErrorType::RendererError);
	}
}

auto Renderer::clearScreen(uint8_t r, uint8_t g, uint8_t b) -> void {
	SDL_SetRenderDrawColor(sdl_renderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(sdl_renderer);
}

auto Renderer::presentScreen() -> void {
	SDL_RenderPresent(sdl_renderer);
}

auto Renderer::renderTexture(SDL_Texture* texture, const Camera& camera, int x, int y, float scale) -> void {
	int tex_width = 0;
	int tex_height = 0;
	SDL_QueryTexture(texture, nullptr, nullptr, &tex_width, &tex_height);
	SDL_Rect dest_rect = { 
		x - camera.pos.x, y - camera.pos.y,
		tex_width * scale * camera.zoom, tex_height * scale * camera.zoom};

	SDL_RenderCopy(sdl_renderer, texture, NULL, &dest_rect);
}

auto Renderer::getWinSize() -> std::pair<int, int> {
	std::pair<int, int> size;
	SDL_GetWindowSize(sdl_window, &size.first, &size.second);
	return size;
}