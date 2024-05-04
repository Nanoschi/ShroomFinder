#include <fstream>
#include "gui/spottings.h"
#include "paths.h"
#include "gui/map.h"
#include "gui/gui_config.h"

auto GuiSpottings::loadData(GuiMap& map) -> void {
	std::ifstream input(paths::SpottingsFile, std::ios::binary);
	for (int i = 0; i < SpottingCategoryCount; i++) {
		categories.push_back({});
		uint32_t item_count;
		input.read((char*)&item_count, sizeof(item_count));
		_loadCategory(input, item_count, &categories[categories.size() - 1]);
	}
	uint32_t spotting_count;
	input.read((char*)&spotting_count, sizeof(spotting_count));
	_loadCoordinates(input, map, spotting_count);
}

auto GuiSpottings::render() -> void {

}

auto GuiSpottings::_loadCoordinates(std::ifstream& file, GuiMap& map, unsigned count) -> void {
	world_coords.reserve(count);

	for (unsigned i = 0; i < count; i++) {
		double latitude, longitude;
		unsigned short phylum, animal_class, order, family, genus, scient_name;
		file.read((char*)&latitude, sizeof(latitude));
		file.read((char*)&longitude, sizeof(longitude));
		file.read((char*)&phylum, sizeof(phylum));
		file.read((char*)&animal_class, sizeof(animal_class));
		file.read((char*)&order, sizeof(order));
		file.read((char*)&family, sizeof(family));
		file.read((char*)&genus, sizeof(genus));
		file.read((char*)&scient_name, sizeof(scient_name));

		const glm::vec2 world_coord = map.geoToWorld({ longitude, latitude });
		world_coords.push_back(world_coord);
	}	
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