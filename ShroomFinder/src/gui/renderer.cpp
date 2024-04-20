#include "SDL_image.h"
#include "gui/renderer.h"
#include "error.h"
#include "opengl/debug.h"

Renderer::Renderer(int win_width, int win_height, const std::string& title) {
	_initGraphicsSystem(win_width, win_height, title);
}

auto Renderer::clearScreen(GLclampf r, GLclampf g, GLclampf b) -> void {
	glClearColor(r, g, b, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

auto Renderer::presentScreen() -> void {
	SDL_RenderPresent(sdl_renderer);
}

auto Renderer::renderTexture(SDL_Texture* texture, const Camera& camera, int x, int y, float scale) -> void {
	int tex_width = 0;
	int tex_height = 0;
	SDL_QueryTexture(texture, nullptr, nullptr, &tex_width, &tex_height);
	SDL_Rect dest_rect = { 
		x + camera.pos.x,
		y + camera.pos.y,
		tex_width * scale * camera.zoom,
		tex_height * scale * camera.zoom };

	SDL_RenderCopy(sdl_renderer, texture, NULL, &dest_rect);
}

auto Renderer::getWinSize() -> std::pair<int, int> {
	std::pair<int, int> size;
	SDL_GetWindowSize(sdl_window, &size.first, &size.second);
	return size;
}

auto Renderer::_initGraphicsSystem(int win_width, int win_height, const std::string& title) -> void {
	// SDL Init
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	sdl_window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		win_width, win_height,
		SDL_WINDOW_OPENGL);

	if (sdl_window == nullptr) {
		reportError(ErrorType::WindowError);
	}

	//sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);

	if (false) {
		reportError(ErrorType::RendererError);
	}

	// OpenGL Init
	gl_context = SDL_GL_CreateContext(sdl_window);

	// Glew Init
	GLenum glew_error = glewInit();
	if (glew_error != GLEW_OK) {
		fprintf(stderr, (const char*)glewGetErrorString(glew_error));
	}

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(openglDebugCallback, nullptr);
}