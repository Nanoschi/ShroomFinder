#pragma once
#include "gui/display.h"
#include "input_reader.h"

class App {
private:
	bool running;

	Display display;
	InputReader input_reader;
public:
	App();

	auto run() -> void;

	auto close() -> void;

private:
	auto _applyInput() -> void;
};
