#include "input_reader.h"

InputReader::InputReader() : 
	keys{},
	mouse_pos{0, 0},
	delta_mouse{0, 0},
	scroll{0},
	has_quit{false},
	left_mouse{false}, middle_mouse{false}, right_mouse{false}
{ }

auto InputReader::pollInput() -> void {
	delta_mouse = { 0, 0 };
	scroll = 0;
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			has_quit = true;
		}

		if (event.type == SDL_KEYDOWN) {
			SDL_Keycode key = event.key.keysym.sym;
			SDL_KeyCode key_code = _convertKeyCode(key);
			keys[key_code] = true;
		}
		else if (event.type == SDL_KEYUP) {
			SDL_Keycode key = event.key.keysym.sym;
			SDL_KeyCode key_code = _convertKeyCode(key);
			keys[key_code] = false;
		}
		else if (event.type == SDL_MOUSEMOTION) {
			int x = event.motion.x;
			int y = event.motion.y;
			int dx = event.motion.xrel;
			int dy = event.motion.yrel;
			_updateMousePos(x, y, dx, dy);
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN) {
			Uint8 button = event.button.button;
			_updateMouseButton(button, true);
		}
		else if (event.type == SDL_MOUSEBUTTONUP) {
			Uint8 button = event.button.button;
			_updateMouseButton(button, false);
		}
		else if (event.type == SDL_MOUSEWHEEL) {
			scroll = event.wheel.preciseY;
		}
	}
}

auto InputReader::getMousePos() -> glm::vec2 {
	return mouse_pos;
}

auto InputReader::getDeltaMousePos() -> glm::vec2 {
	return delta_mouse;
}

auto InputReader::getScrollAmount() -> float {
	return scroll;
}

auto InputReader::getMouseLeft() -> bool {
	return left_mouse;
}

auto InputReader::getMouseRight() -> bool {
	return right_mouse;
}

auto InputReader::getMouseMiddle() -> bool {
	return middle_mouse;
}

auto InputReader::hasQuit() -> bool {
	return has_quit;
}


auto InputReader::isKeyDown(SDL_KeyCode key) -> bool {
	SDL_KeyCode key_code = _convertKeyCode(key);
	if (keys.contains(key_code)) {
		return keys[key_code];
	}

	return false;
}

auto InputReader::clearKeys() -> void {
	for (auto& pair : keys) {
		pair.second = false;
	}
}

auto InputReader::_convertKeyCode(SDL_Keycode keycode) -> SDL_KeyCode {
	return static_cast<SDL_KeyCode>(keycode);
}

auto InputReader::_updateMousePos(int x, int y, int dx, int dy) -> void {
	mouse_pos = { x, y };
	delta_mouse = { dx, dy };
}

auto InputReader::_updateMouseButton(Uint8 button, bool value) -> void {
	switch (button) {
	case 1:
		left_mouse = value;
		return;
	case 3:
		right_mouse = value;
		return;
	case 2:
		middle_mouse = value;
		return;
	}
}