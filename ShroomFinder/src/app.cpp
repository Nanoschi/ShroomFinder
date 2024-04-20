#pragma once
#include <algorithm>
#include "SDL.h"

#include "app.h"

#include "opengl/vertex_buffer.h"
#include "opengl/vertices.h"
#include "opengl/shader_program.h"

App::App() {
	running = true;
}

auto App::run() -> void {
	std::array<glm::vec2, 3> vertices;
	getTestTriangleVertices(&vertices);

	VertexBuffer vbo;
	vbo.bind();
	vbo.loadData(sizeof(vertices), (char*)&vertices);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), NULL);
	glEnableVertexAttribArray(0);
	ShaderProgram program;
	program.loadShadersFromFile("resources/shaders/shader.vert", "resources/shaders/shader.frag");
	program.use();

	while (!input_reader.hasQuit()) {
		input_reader.pollInput();
		_applyInput();
		//display.drawFrame();
		//display.renderer.clearScreen(255, 0, 0);
		glClearColor(1.0, 0.2, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		
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
