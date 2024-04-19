#pragma once
#include <algorithm>
#include "SDL.h"

#include "app.h"

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
}
