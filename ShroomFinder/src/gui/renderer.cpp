#include "SDL_image.h"
#include "gui/renderer.h"
#include "error.h"

#include "opengl/debug.h"
#include "opengl/vertices.h"
#include "opengl/vertex_buffer.h"

Renderer::Renderer(int win_width, int win_height, const std::string& title) {
	_initGraphicsSystem(win_width, win_height, title);
	texture_renderer.init();
}

auto Renderer::clearScreen(GLclampf r, GLclampf g, GLclampf b) -> void {
	glClearColor(r, g, b, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

auto Renderer::presentScreen() -> void {
	SDL_GL_SwapWindow(sdl_window);
}

auto Renderer::getWinSize() -> glm::ivec2 {
	glm::ivec2 size;
	SDL_GetWindowSize(sdl_window, &size.x, &size.y);
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

	SDL_GL_SetSwapInterval(0);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(openglDebugCallback, nullptr);
}