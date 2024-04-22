#include <iostream>
#include <string>
#include "load_file.h"

#include "stb_image.h"

auto loadTextFile(const std::string& path) -> std::string {
	std::ifstream input(path, std::ios::binary);

	if (!input) {
		std::cerr << "Failed to open file: " << path << std::endl;
		return "";
	}
	
	input.seekg(0, input.end);
	std::streampos size = input.tellg();
	input.seekg(0, input.beg);

	std::string file_content;
	file_content.resize(size);
	
	input.read((char*)file_content.c_str(), size);
	return file_content;
}

auto loadTexture(const std::string path) -> Texture {
	const char* c_str = path.c_str();
	int width, height, channels;
	stbi_uc* data = stbi_load(c_str, &width, &height, &channels, 0);

	Texture texture;
	texture.createTexture();
	texture.loadDataFromMemory((char*)data, width, height);
	stbi_image_free(data);
	return texture;
}