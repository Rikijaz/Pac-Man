// Level.h : Defines the Level class's functions

#include "Level.h"

#include <fstream>

Level::Level(Data & data) {
	if (data.GetSprites(TILE_KEY, sprite_list_)) {
		if (ReadMapAndInstantiateTiles(data)) {
			std::cout << "Level has successfully loaded.\n";
		}
	}
	else {
		std::cout << "Level has failed to load.\n";
	}
}

void Level::Render(Graphics & graphics) {
	for (unsigned i = 0; i < tiles_.size(); ++i) {
		tiles_.at(i)->Render(graphics);
	}
}

std::vector<Tile*> Level::GetTiles() {
	return tiles_;
}

bool Level::ReadMapAndInstantiateTiles(Data &data) {
	// Success flag
	bool tiles_loaded = true;

	//Open the map
	std::ifstream map(MAP_FILE_PATH_);

	// If the map couldn't be loaded
	if (!map.is_open()) {
		std::cout << "Unable to load map file!\n";
		tiles_loaded = false;
	}
	else {
		// The tile offsets
		int x = 0, y = 0;

		// Initialize the tiles
		for (int i = 0; i < TOTAL_TILES_; ++i) {
			// Determines what kind of tile will be made
			int tile_type = -1;

			std::string parsed;
			// Read tile from map file
			map >> parsed;

			tile_type = std::stoi(parsed);
			// std::cout << tile_type << "\n";

			// If the was a problem in reading the map
			if (map.fail()) {
				//Stop loading map
				std::cout << "Error loading map: Unexpected end of file!\n";
				tiles_loaded = false;
				break;
			}

			// If the number is a valid tile number
			if ((tile_type >= 1) && (tile_type < sprite_list_.size() + 1)) {

				tiles_.push_back(new Tile(sprite_list_.at(tile_type - 1), x, y, tile_type));
			}
			// If we don't recognize the tile type
			else if (tile_type == 0) {

			}
			else {
				// Stop loading map
				std::cout << "Error loading map: Invalid tile type at " << i << "\n";
				tiles_loaded = false;
				break;
			}
			// Move to next tile spot
			x += TILE_WIDTH_;

			// If we've gone too far
			if (x >= GLOBALS::LEVEL_WIDTH) {

				// Move back
				x = 0;

				// Move to the next row
				y += TILE_HEIGHT_;
			}
		}
	}

	// Close the file
	map.close();

	// If the map was loaded fine
	return tiles_loaded;
}