#pragma once
#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "camera.h"
#include "renderer.h"
#include "gui/map.h"

class Display {
public:
	Renderer renderer;

	Camera camera;
	
	GuiMap map;

	Display();

	auto drawFrame() -> void;

	auto moveCamera(glm::vec2 delta) -> void;

	auto zoomIn() -> void;

	auto zoomOut() -> void;

private:
	auto _loadData() -> void;
};