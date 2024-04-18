#pragma once
#include "gui/display.h"

class App {
private:
	bool running;

	Display display;

	glm::vec2 mouse_pos;
	glm::vec2 delta_mouse_pos;
	uint32_t mouse_buttons;
	float scroll;

public:
	App();

	auto run() -> void;

	auto close() -> void;

private:
	auto _pollInput() -> void;

	auto _updateMousePos(int x, int y) -> void;

	auto _tryMoveCamera() -> void;
};
