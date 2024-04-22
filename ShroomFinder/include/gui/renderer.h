#pragma once
#include <utility>
#include <string>

#include "SDL.h"

#include "camera.h"
#include "opengl/vertex_buffer.h"
#include "opengl/vertex_array.h"
#include "opengl/shader_program.h"

class Renderer {
public:
	SDL_Renderer* sdl_renderer;
	SDL_Window* sdl_window;
	SDL_GLContext gl_context;

	VertexBuffer texture_vbo;
	VertexArray texture_vao;
	ShaderProgram texture_program;
	GLint texture_scale_uniform;
	GLint texture_pos_uniform;

	//VertexBuffer texture_quad_vertices;

	Renderer(int win_width, int win_height, const std::string& title);

	auto clearScreen(GLclampf r, GLclampf g, GLclampf b) -> void;

	auto presentScreen() -> void;

	auto renderTexture(SDL_Texture* texture, const Camera& camera, int x, int y, float scale = 1.0f) -> void;

	auto getWinSize() -> std::pair<int, int>;

	auto renderBoundTexture() -> void;

	auto setTextureScaleUniform(glm::vec2 scale) -> void;

	auto setTexturePositionUniform(glm::vec2 position) -> void;

private:
	auto _initGraphicsSystem(int win_width, int win_height, const std::string& title) -> void;

	auto _initTextureVertexBuffer() -> void;

	auto _initTextureVertexProgram() -> void;

	auto _initTextureUniforms() -> void;
};