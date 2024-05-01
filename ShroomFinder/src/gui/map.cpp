#pragma once
#include <thread>

#include "gui/map.h"
#include "gui/gui_config.h"
#include "load_file.h"
#include "paths.h"
#include "gui/image.h"
#include "stb_image.h"

#include "glm.hpp"
#include "ext.hpp"

GuiMap::GuiMap() {
	large_map_textures.resize(LargeMapTileXCount * LargeMapTileYCount);
}

auto GuiMap::loadData() -> void {
	_loadLargeTiles(paths::LargeTileDir);
	float half_tile_width = largeTileAt(0, 0).getAspect();
	float half_tile_height = 1;
	map_pos = { half_tile_width, -half_tile_height };
}

auto GuiMap::render(Renderer& renderer, Camera& camera) -> void {
	TextureRenderer& tex_renderer = renderer.texture_renderer;
	tex_renderer.getShaderProgram().use();

	float texture_aspect = largeTileAt(0, 0).getAspect();

	glm::vec2 texture_scale{ texture_aspect, 1 };
	tex_renderer.setTextureScale(texture_scale);
	tex_renderer.setTextureZoom(camera.zoom);


	for (int x = 0; x < LargeMapTileXCount; x++) {
		for (int y = 0; y < LargeMapTileYCount; y++) {
			const glm::vec2 texture_offset = { x * texture_aspect * 2, -y * 2 };
			tex_renderer.setTexturePosition(camera.pos + texture_offset + map_pos);

			Texture& texture = largeTileAt(x, y);
			texture.bind();
			tex_renderer.renderBoundTexture();
		}
	}
}

auto GuiMap::largeTileAt(int x, int y) -> Texture& {
	return large_map_textures.at(y * LargeMapTileXCount + x);
}

auto GuiMap::smallTileAt(int x, int y) -> Texture& {
	return largeTileAt(x, y);
}

auto GuiMap::getMapWidth() -> float {
	return LargeMapTileXCount * 2 * largeTileAt(0, 0).getAspect();
}

auto GuiMap::getMapHeight() -> float {
	return LargeMapTileYCount * 2; // each tile has a height of 1
}

auto GuiMap::worldToGeo(glm::vec2 world_pos) -> glm::vec2 {
	const glm::vec2 flipped_world_pos = glm::vec2(world_pos.x, -world_pos.y);
	const glm::vec2 normal_pos = flipped_world_pos / glm::vec2{getMapWidth(), getMapHeight()};
	const glm::vec2 flipped_normal_pos = glm::vec2(normal_pos.x, 1 - normal_pos.y);
	const float adjustment_scale = -4.0f * (flipped_normal_pos.y - 0.5f) * (flipped_normal_pos.y - 0.5f) + 1;
	const glm::vec2 geo_pos = flipped_normal_pos * GeoSize + GeoMin;
	const glm::vec2 adjusted_geo_pos = { geo_pos.x, geo_pos.y + adjustment_scale * MapProjectionAdjustmentFactor };
	
	return adjusted_geo_pos;
}

auto GuiMap::geoToWorld(glm::vec2 geo_pos) -> glm::vec2 {
	const glm::vec2 relative_geo_pos = geo_pos - GeoMin;
	const glm::vec2 normal_pos = relative_geo_pos / GeoSize;
	const float adjustment_scale = -4.0f * (normal_pos.y - 0.5f) * (normal_pos.y - 0.5f) + 1;
	const glm::vec2 flipped_normal_pos{ normal_pos.x, -(1 - normal_pos.y) };
	const glm::vec2 world_pos = flipped_normal_pos * glm::vec2(getMapWidth(), getMapHeight());
	const glm::vec2 adjusted_world_pos{ world_pos.x, world_pos.y - adjustment_scale * MapProjectionAdjustmentFactor };

	return adjusted_world_pos;
}

auto GuiMap::_loadLargeTiles(const std::string& directory) -> void {
	std::vector<std::thread> threads;
	constexpr int thread_count = LargeMapTileXCount + LargeMapTileYCount;

	std::vector<ImageData> images(LargeMapTileXCount * LargeMapTileYCount);

	auto thread_fun = [&](int x, int y) {
		std::string file_name = this->_getFileNameString(x, y);
		std::string path = paths::LargeTileDir + "/" + file_name;
		
		const char* c_path = path.c_str();
		ImageData& img = images[y * LargeMapTileXCount + x];
		img.data = stbi_load(c_path, &img.width, &img.height, NULL, 0);
		};


	for (int x = 0; x < LargeMapTileXCount; x++) {
		for (int y = 0; y < LargeMapTileYCount; y++) {
			threads.push_back(std::thread(thread_fun, x, y));
		}
	}

	for (auto& thread : threads) {
		thread.join();
	}

	for (int x = 0; x < LargeMapTileXCount; x++) {
		for (int y = 0; y < LargeMapTileYCount; y++) {
			int idx = y * LargeMapTileXCount + x;
			ImageData img = images[idx];
			Texture texture;
			texture.createTexture();
			texture.bind();
			texture.loadTextureFromMemory((char*)img.data, img.width, img.height);
			largeTileAt(x, y) = texture;
			stbi_image_free(img.data);
		}
	}
}

auto GuiMap::_getFileNameString(int x, int y) -> std::string {
	const std::string file_name_base = "germany_";
	const std::string file_type = ".jpg";
	return file_name_base + std::to_string(x) + "_" + std::to_string(y) + file_type;
}
