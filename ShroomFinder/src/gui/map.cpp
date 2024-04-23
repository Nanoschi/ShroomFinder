#pragma once
#include <thread>

#include "gui/map.h"
#include "gui/gui_config.h"
#include "load_file.h"
#include "paths.h"
#include "gui/image.h"
#include "stb_image.h"

GuiMap::GuiMap() {
	large_map_textures.resize(LargeMapTileXCount * LargeMapTileYCount);
}

auto GuiMap::loadData() -> void {
	_loadLargeTiles(paths::LargeTileDir);
}

auto GuiMap::render(Renderer& renderer, const Camera& camera) -> void {
	TextureRenderer& tex_renderer = renderer.texture_renderer;
	tex_renderer.getShaderProgram().use();
	
	float texture_aspect = largeTileAt(0, 0).getAspect();

	tex_renderer.setTexturePosition({ 0, 0 });
	tex_renderer.setTextureScale({ texture_aspect, 1 });

	for (int x = 0; x < 1; x++) {
		for (int y = 0; y < 1; y++) {
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
