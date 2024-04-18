#pragma once
#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "camera.h"
#include "renderer.h"

class Display {
public:
	Renderer renderer;

	Camera camera;

	SDL_Texture* map_texture;

	Display();

	auto drawFrame() -> void;

	auto moveCamera(glm::vec2 delta) -> void;

	auto zoomCamera(float delta) -> void;

	auto zoomCameraTo(float zoom) -> void;

private:
	auto _loadData() -> void;
};