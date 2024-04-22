#include "SDL_image.h"
#include "gui/renderer.h"
#include "error.h"

#include "opengl/debug.h"
#include "opengl/vertices.h"
#include "opengl/vertex_buffer.h"

Renderer::Renderer(int win_width, int win_height, const std::string& title) {
	_initGraphicsSystem(win_width, win_height, title);
	_initTextureVertexBuffer();
	_initTextureVertexProgram();  
	_initTextureUniforms();
}

auto Renderer::clearScreen(GLclampf r, GLclampf g, GLclampf b) -> void {
	glClearColor(r, g, b, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

auto Renderer::presentScreen() -> void {
	SDL_GL_SwapWindow(sdl_window);
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

auto Renderer::setTextureScaleUniform(glm::vec2 scale) -> void {
	texture_program.use();
	glUniform2f(texture_scale_uniform, scale.x, scale.y);
}

auto Renderer::setTexturePositionUniform(glm::vec2 position) -> void {
	texture_program.use();
	glUniform2f(texture_pos_uniform, position.x, position.y);
}

auto Renderer::renderBoundTexture() -> void {
	texture_vao.bind();
	texture_vbo.bind();
	texture_program.use();
	glDrawArrays(GL_TRIANGLES, 0, 6);
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

auto Renderer::_initTextureVertexBuffer() -> void {
	std::array<TextureVertex, 6> vertices;
	getTextureQuadVertices(&vertices);

	texture_vao.createVertexArray();
	texture_vao.bind();

	texture_vbo.createBuffer();
	texture_vbo.bind();
	texture_vbo.loadData(sizeof(vertices), (char*)&vertices);

	texture_vao.addAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), offsetof(TextureVertex, position));
	texture_vao.addAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), offsetof(TextureVertex, uv));

}

auto Renderer::_initTextureVertexProgram() -> void {
	texture_program.createProgram();
	texture_program.loadShadersFromFile("resources/shaders/shader.vert", "resources/shaders/shader.frag");
}

auto Renderer::_initTextureUniforms() -> void {
	texture_scale_uniform = glGetUniformLocation(texture_program.getProgramId(), "u_scale");
	texture_pos_uniform = glGetUniformLocation(texture_program.getProgramId(), "u_position");
}