#pragma once
#include <vector>
#include <filesystem>

#include "gui/image.h"
#include "gui/renderer.h"
#include "opengl/texture.h"
#include "gui/camera.h"

class GuiMap {
	std::vector<Texture> large_map_textures;
	glm::vec2 map_pos;

public:
	GuiMap();

	auto loadData() -> void;

	auto render(Renderer& renderer, Camera& camera) -> void;

	auto largeTileAt(int x, int y) -> Texture&;

	auto smallTileAt(int x, int y) -> Texture&;

	auto getMapWidth() -> float;

	auto getMapHeight() -> float;

private:
	auto _loadLargeTiles(const std::string& directory) -> void;

	auto _getFileNameString(int x, int y) -> std::string;
};