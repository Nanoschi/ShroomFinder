#pragma once
#include <vector>
#include <fstream>
#include <map>

#include "vec2.hpp"
#include "gui/map.h"

struct Spotting {
	float latitude;
	float longitude;
};

class GuiSpottings {
public:
	std::vector<glm::vec2> world_coords;
	std::vector<std::map<std::string, uint16_t>> categories;

	auto render() -> void;

	auto loadData(GuiMap& map) -> void;

private:
	auto _loadCoordinates(std::ifstream& file, GuiMap& map, unsigned count) -> void;

	auto _loadCategory(std::ifstream& file, unsigned count, std::map<std::string, uint16_t>* out_indices) -> void;
};