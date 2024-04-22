#pragma once
#include <vector>
#include <filesystem>

#include "gui/image.h"
#include "gui/renderer.h"
#include "opengl/texture.h"

class GuiMap {
	std::vector<ImageData> large_map_tiles;

	auto render(Renderer& renderer, const Camera& camera) -> void;

private:
	auto _loadTiles(std::vector<ImageData>* out_tiles, int x_count, int y_count, std::filesystem::path directory) -> void;
};