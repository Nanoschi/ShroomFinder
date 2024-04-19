#pragma once
#include <unordered_map>

#include "vec2.hpp"
#include "SDL.h"

class InputReader {
private:
	std::unordered_map<SDL_KeyCode, bool> keys;

	glm::vec2 mouse_pos;
	glm::vec2 delta_mouse;
	float scroll;
	bool left_mouse, right_mouse, middle_mouse;

	bool has_quit;

public:
	InputReader();

	auto pollInput() -> void;

	auto getMousePos() -> glm::vec2;

	auto getDeltaMousePos() -> glm::vec2;

	auto getScrollAmount() -> float;

	auto getMouseLeft() -> bool;

	auto getMouseRight() -> bool;

	auto getMouseMiddle() -> bool;


	auto isKeyDown(SDL_KeyCode key) -> bool;

	auto clearKeys() -> void;

	auto hasQuit() -> bool;

private:
	auto _convertKeyCode(SDL_Keycode keycode) -> SDL_KeyCode;

	auto _updateMousePos(int x, int y, int dx, int dy) -> void;

	auto _updateMouseButton(Uint8 button, bool value) -> void;
};