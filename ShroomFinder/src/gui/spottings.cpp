#include "gui/spottings.h"
#include <fstream>
#include "paths.h"
#include "gui/map.h"
#include "gui/gui_config.h"

auto GuiSpottings::loadData() -> void {
	std::ifstream input(paths::SpottingsFile, std::ios::binary);
	for (int i = 0; i < SpottingCategoryCount; i++) {
		categories.push_back({});
		uint32_t item_count;
		input.read((char*)&item_count, sizeof(item_count));
		_loadCategory(input, item_count, &categories[categories.size() - 1]);
	}
}

auto GuiSpottings::render() -> void {

}

auto GuiSpottings::_loadCoordinates(std::ifstream& file, GuiMap& map, unsigned count) -> void {
	double latitude, longitude;
	unsigned short scient_name, phylum, animal_class, order, family, genus;
	file 
		>> latitude >> longitude 
		>> scient_name >> phylum >> animal_class >> order >> family >> genus;

	const glm::vec2 world_coord = map.geoToWorld({ latitude, longitude });
	world_coords.reserve(count);
	world_coords.push_back(world_coord);
}

auto GuiSpottings::_loadCategory(std::ifstream& file, unsigned count, std::map<std::string, uint16_t>* out_indices) -> void {
	for (uint16_t i = 0; i < count; i++) {
		std::string value;
		char c;
		file.get(c);
		while (c != '\0') {
			value.push_back(c);
			file.get(c);
		}
		(*out_indices)[value] = i;
	}
}