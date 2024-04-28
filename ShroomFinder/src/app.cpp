#pragma once
#include <chrono>
#include <iostream>

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
	using namespace std::chrono_literals;

	auto start_time = std::chrono::high_resolution_clock::now();
	int frame_count = 0;
	while (!input_reader.hasQuit()) {

		input_reader.pollInput();
		_applyInput();
		display.drawFrame();
		frame_count++;

		auto current_time = std::chrono::high_resolution_clock::now();
		auto elapsed_time = current_time - start_time;
		auto elapsed_time_ms = std::chrono::duration_cast<std::chrono::microseconds>(elapsed_time);
		
		if (elapsed_time_ms >= 1000ms) {
			int elapsed_micro_int = elapsed_time_ms.count();
			float elapsed_milli_float = static_cast<float>(elapsed_micro_int) / 1000;
			float fps = frame_count;
			std::cout << "FPS: " << fps << " | Frame Time: " << elapsed_milli_float / frame_count << "ms\n";
			frame_count = 0;
			start_time = std::chrono::high_resolution_clock::now();
		}
	}
}

auto App::close() -> void {

}

auto App::_applyInput() -> void {
	if (input_reader.getMouseMiddle()) {
		display.camera.move(input_reader.getDeltaMousePos());
	}
	if (input_reader.getScrollAmount() < 0) {
		glm::vec2 mouse_pos = input_reader.getMousePos();
		glm::vec2 screen_mouse_pos = display.camera.RasterToScreen(mouse_pos, display.renderer.getWinSizeF());
		display.zoomOut(screen_mouse_pos);
	}
	else if (input_reader.getScrollAmount() > 0) {
		glm::vec2 mouse_pos = input_reader.getMousePos();
		glm::vec2 screen_mouse_pos = display.camera.RasterToScreen(mouse_pos, display.renderer.getWinSizeF());
		display.zoomIn(screen_mouse_pos);
	}
}
