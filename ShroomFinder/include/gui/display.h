#pragma once
#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "camera.h"
#include "renderer.h"
#include "gui/map.h"
#include "gui/spottings.h"

class Display {
public:
	Renderer renderer;

	Camera camera;
	
	GuiMap map;
	GuiSpottings spottings;

	Display();

	auto drawFrame() -> void;

	auto moveCamera(glm::vec2 delta) -> void;

	auto zoomIn(glm::vec2 target) -> void;

	auto zoomOut(glm::vec2 target) -> void;

private:
	auto _loadData() -> void;
};