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
	while (!input_reader.hasQuit()) {
		input_reader.pollInput();
		_applyInput();
		display.drawFrame();
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
