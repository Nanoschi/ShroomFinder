#include <iostream>
#include "load_file.h"

auto loadTextFile(const std::string& path) -> std::string {
	std::ifstream input(path, std::ios::binary);

	if (!input) {
		std::cerr << "Failed to open file: " << path << std::endl;
		return "";
	}
	
	std::string content;
	char c;
	while (input >> c) {
		content.push_back(c);
	}

	input.close();
	return content;
}