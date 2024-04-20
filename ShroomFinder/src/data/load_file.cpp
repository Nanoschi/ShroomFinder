#include <iostream>
#include <string>
#include "load_file.h"

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