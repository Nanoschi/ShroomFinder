#pragma once
#include "gui/display.h"

class App {
private:
	bool running;

	Display display;

public:
	App();

	auto run() -> void;

	auto close() -> void;

private:
	auto _pollInput() -> void;
};
