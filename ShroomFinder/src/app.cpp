#pragma once
#include <algorithm>
#include "SDL.h"

#include "app.h"

#include "opengl/vertex_buffer.h"
#include "opengl/vertices.h"
#include "opengl/shader_program.h"
#include "opengl/texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

App::App() {
	running = true;
}

auto App::run() -> void {
	std::array<TextureVertex, 3> vertices;
	getTextureQuadVertices(&vertices);

	VertexBuffer vbo;
	vbo.createBuffer();
	vbo.bind();
	vbo.loadData(sizeof(vertices), (char*)&vertices);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), NULL);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void*)offsetof(TextureVertex, uv));
	glEnableVertexAttribArray(1);

	int width = 0;
	int height = 0;
	int channels = 0;
	stbi_uc* img = stbi_load("resources/germany_0_11.jpg", &width, &height, &channels, 0);
	Texture texture;
	texture.bind();
	texture.loadDataFromBuffer((char*)img, width, height);
	stbi_image_free(img);

	ShaderProgram program;
	program.loadShadersFromFile("resources/shaders/shader.vert", "resources/shaders/shader.frag");
	program.use();

	while (!input_reader.hasQuit()) {
		input_reader.pollInput();
		_applyInput();
		//display.drawFrame();
		display.renderer.clearScreen(0.9, 0.6, 0.8);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//display.renderer.presentScreen();
		SDL_GL_SwapWindow(display.renderer.sdl_window);
	}
}

auto App::close() -> void {

}

auto App::_applyInput() -> void {
	if (input_reader.getMouseMiddle()) {
		display.camera.move(input_reader.getDeltaMousePos());
	}
	if (input_reader.getScrollAmount() < 0) {
		display.zoomOut();
	}
	else if (input_reader.getScrollAmount() > 0) {
		display.zoomIn();
	}
}
