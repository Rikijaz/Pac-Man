// Level.h : Defines the Level class's functions

#include "Level.h"

#include <fstream>

Level::~Level() {
	for (unsigned i = 0; i < teleport_tiles_.size(); ++i) {
		delete teleport_tiles_.at(i);
		teleport_tiles_.at(i) = nullptr;
	}
	for (unsigned i = 0; i < collision_tiles_.size(); ++i) {
		delete collision_tiles_.at(i);
		collision_tiles_.at(i) = nullptr;
	}

	for (unsigned i = 0; i < pac_dots_.size(); ++i) {
		delete pac_dots_.at(i);
		pac_dots_.at(i) = nullptr;
	}

	for (unsigned i = 0; i < pac_pellets_.size(); ++i) {
		delete pac_pellets_.at(i);
		pac_pellets_.at(i) = nullptr;
	}
}

Level::Level(Data & data) {
	if (data.GetSprites(TILE_KEY, sprite_list_)) {
		if (ReadMapAndInstantiateTiles(data)) {
			std::cout << "Level has successfully loaded!\n";
		}
	}
	else {
		std::cout << "Level has failed to load!\n";
	}
}

void Level::Render(Graphics & graphics) {
	for (unsigned i = 0; i < collision_tiles_.size(); ++i) {
		collision_tiles_.at(i)->Render(graphics);
	}

	for (unsigned i = 0; i < pac_dots_.size(); ++i) {
		pac_dots_.at(i)->Render(graphics);
	}

	for (unsigned i = 0; i < pac_pellets_.size(); ++i) {
		pac_pellets_.at(i)->Render(graphics);
	}
}

void Level::SetCharacterTilePos(int char_key, int tile_pos_x, int tile_pos_y) {
	character_tile_pos[char_key].tile_pos_x_ = tile_pos_x;
	character_tile_pos[char_key].tile_pos_x_ = tile_pos_y;;
}

int Level::GetCharacterTilePosX(int char_key) {
	return character_tile_pos[char_key].tile_pos_x_;
}

int Level::GetCharacterTilePosY(int char_key) {
	return character_tile_pos[char_key].tile_pos_y_;
}

std::vector<Tile*> Level::GetTeleportTiles() {
	return teleport_tiles_;
}

std::vector<Tile*> Level::GetCollisionTiles() {
	return collision_tiles_;
}

std::vector<Tile*> Level::GetPacDots() {
	return pac_dots_;
}

std::vector<Tile*> Level::GetPacPellets() {
	return pac_pellets_;
}

void Level::RemovePacDot(int index) {
	delete pac_dots_.at(index);
	pac_dots_.erase(pac_dots_.begin() + index);
}

void Level::RemovePacPellet(int index) {
	delete pac_pellets_.at(index);
	pac_pellets_.erase(pac_pellets_.begin() + index);
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
			if ((tile_type >= 1) && (tile_type <= TOTAL_COLLISION_TILES_)) {
				collision_tiles_.push_back(new Tile(sprite_list_.at(tile_type - 1), x, y, tile_type));
			}
			else if (tile_type == TOTAL_PAC_DOTS_) {
				pac_dots_.push_back(new Tile(sprite_list_.at(tile_type - 1), x, y, tile_type));
			}
			else if (tile_type == TOTAL_PAC_PELLETS_) {
				pac_pellets_.push_back(new Tile(sprite_list_.at(tile_type - 1), x, y, tile_type));
			}
			else if (tile_type == LEFT_TELEPORT_TILE_) {
				// Left teleport entry
				teleport_tiles_.push_back(new Tile(sprite_list_.at(tile_type - 1), x + L_TELE_ENTRY_POS_X_OFFSET_, y, tile_type));
				// Right teleport exit
				teleport_tiles_.push_back(new Tile(sprite_list_.at(tile_type - 1), x + R_TELE_EXIT_POS_X_OFFSET_, y, tile_type));
			}
			else if (tile_type == RIGHT_TELEPORT_TILE_) {
				// Left teleport exit
				teleport_tiles_.push_back(new Tile(sprite_list_.at(tile_type - 1), x + L_TELE_EXIT_POS_X_OFFSET_, y, tile_type));
				// Right teleport entry
				teleport_tiles_.push_back(new Tile(sprite_list_.at(tile_type - 1), x + R_TELE_ENTRY_POS_X_OFFSET_, y, tile_type));
			}
			else if (tile_type == 0) {

			}
			// If we don't recognize the tile type
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