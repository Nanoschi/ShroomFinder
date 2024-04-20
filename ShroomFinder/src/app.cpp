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

	ShaderProgram program;
	program.loadShadersFromFile(
		"resources/shaders/shader.vert",
		"resources/shaders/shader.frag"
	);
	program.use();

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
	glEnableVertexAttribArray(0);

	while (!input_reader.hasQuit()) {
		input_reader.pollInput();
		_applyInput();
		display.drawFrame();
		glDrawArrays(GL_TRIANGLES, 0, 3);
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
