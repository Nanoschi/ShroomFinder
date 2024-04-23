#pragma once
#include <vector>
#include <filesystem>

#include "gui/image.h"
#include "gui/renderer.h"
#include "opengl/texture.h"

class GuiMap {
	std::vector<Texture> large_map_textures;

public:
	GuiMap();

	auto loadData() -> void;

	auto render(Renderer& renderer, const Camera& camera) -> void;

	auto largeTileAt(int x, int y) -> Texture&;

	auto smallTileAt(int x, int y) -> Texture&;

private:
	auto _loadLargeTiles(const std::string& directory) -> void;

	auto _getFileNameString(int x, int y) -> std::string;
};