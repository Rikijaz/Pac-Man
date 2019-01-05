// Level.cpp : Defines the Level class's functions

#include "Level.h"

#include <fstream>

Level::~Level() {
	for (unsigned i = 0; i < path_tiles_.size(); ++i) {
		delete path_tiles_.at(i);
		path_tiles_.at(i) = nullptr;
	}

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
			SetMapNeighbors();
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

void Level::SetCharacterGridTile(int char_key, int tile_pos_x, int tile_pos_y) {
	character_tile_pos[char_key].x_ = tile_pos_x;
	character_tile_pos[char_key].y_ = tile_pos_y;
}

void Level::ResetGridTilesDistance() {
	for (unsigned y = 0; y < LEVEL_HEIGHT_ - 5; ++y) {
		for (unsigned x = 0; x < LEVEL_WIDTH_; ++x) {
			grid_map_[x][y].distance_ = INT_MAX;
		}	
	}
}

GridTile Level::GetCharacterGridTile(int char_key) {
	return character_tile_pos[char_key];
}

int Level::GetCharacterGridTileX(int char_key) {
	return character_tile_pos[char_key].x_;
}

int Level::GetCharacterGridTileY(int char_key) {
	return character_tile_pos[char_key].y_;
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

			if (y / TILE_HEIGHT_ >= 3 && y / TILE_HEIGHT_ <= LEVEL_HEIGHT_ - 3) {
				GridTile new_gridtile = { x / TILE_WIDTH_, y / TILE_HEIGHT_, tile_type };
				grid_map_[x / TILE_WIDTH_][y / TILE_HEIGHT_] = new_gridtile;
				//std::cout << grid_map_[x / TILE_WIDTH_][y / TILE_HEIGHT_].type_ << " ";
			}
	
			// If the number is a valid tile number
			if (tile_type == -1) {
			}
			else if (tile_type == 0) {
				path_tiles_.push_back(new Tile(sprite_list_.at(tile_type), x, y, tile_type));
			}
			else if ((tile_type >= 1) && (tile_type <= TOTAL_COLLISION_TILES_)) {
				collision_tiles_.push_back(new Tile(sprite_list_.at(tile_type), x, y, tile_type));
			}
			else if (tile_type == TOTAL_PAC_DOTS_) {
				pac_dots_.push_back(new Tile(sprite_list_.at(tile_type), x, y, tile_type));
			}
			else if (tile_type == TOTAL_PAC_PELLETS_) {
				pac_pellets_.push_back(new Tile(sprite_list_.at(tile_type), x, y, tile_type));
			}
			else if (tile_type == LEFT_TELEPORT_TILE_) {
				// Left teleport entry : 0
				teleport_tiles_.push_back(new Tile(sprite_list_.at(tile_type), x + L_TELE_ENTRY_POS_X_OFFSET_, y, tile_type));
				// Left teleport northern entry : 1
				teleport_tiles_.push_back(new Tile(sprite_list_.at(tile_type), x + L_TELE_ENTRY_POS_X_OFFSET_ + 32, y - 32, tile_type));
				// Left teleport southern entry : 2
				teleport_tiles_.push_back(new Tile(sprite_list_.at(tile_type), x + L_TELE_ENTRY_POS_X_OFFSET_ + 32, y + 32, tile_type));
				// Right teleport exit : 3
				teleport_tiles_.push_back(new Tile(sprite_list_.at(tile_type), x + R_TELE_EXIT_POS_X_OFFSET_, y, tile_type));
			}
			else if (tile_type == RIGHT_TELEPORT_TILE_) {
				// Left teleport exit : 4
				teleport_tiles_.push_back(new Tile(sprite_list_.at(tile_type), x + L_TELE_EXIT_POS_X_OFFSET_, y, tile_type));
				// Right teleport entry : 5
				teleport_tiles_.push_back(new Tile(sprite_list_.at(tile_type), x + R_TELE_ENTRY_POS_X_OFFSET_, y, tile_type));
				// Right teleport northern entry : 6
				teleport_tiles_.push_back(new Tile(sprite_list_.at(tile_type), x + R_TELE_ENTRY_POS_X_OFFSET_ - 32, y - 32, tile_type));
				// Right teleport southern entry : 7
				teleport_tiles_.push_back(new Tile(sprite_list_.at(tile_type), x + R_TELE_ENTRY_POS_X_OFFSET_ - 32, y + 32, tile_type));
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

void Level::SetMapNeighbors() {
	int x = 0;
	for (unsigned y = 0; y < LEVEL_HEIGHT_ - 5; ++y) {
		for (unsigned x = 0; x < LEVEL_WIDTH_; ++x) {
			//std::cout << grid_map_[x][y].type_ << "\n";
			int tile_type = grid_map_[x][y].type_;
			if (tile_type == 0 
				|| tile_type == 32 
				|| tile_type == 33 
				|| tile_type == 34 
				|| tile_type == 35) {
				Pos east_tile = { x + 1, y };
				Pos south_tile = { x, y + 1 };
				Pos west_tile = { x - 1, y };			
				Pos north_tile = { x, y - 1 };

				grid_map_[x][y].neighbors_.push_back(east_tile);
				grid_map_[x][y].neighbors_.push_back(south_tile);
				grid_map_[x][y].neighbors_.push_back(west_tile);
				grid_map_[x][y].neighbors_.push_back(north_tile);

				for (unsigned i = 0; i < grid_map_[x][y].neighbors_.size(); ++i) {
					Pos neighbor_tile = grid_map_[x][y].neighbors_.at(i);
					int tile_type = grid_map_[neighbor_tile.x_][neighbor_tile.y_].type_;
					if (
						!(tile_type == 0 || 
						tile_type == 32 || 
						tile_type == 33 || 
						tile_type == 34 || 
						tile_type == 35)) {
						grid_map_[x][y].neighbors_.erase(grid_map_[x][y].neighbors_.begin() + i);
					}
				}
			}
		}
	}
	
	//x = 0;
	//for (unsigned y = 0; y < LEVEL_HEIGHT_ - 5; ++y) {
	//	for (unsigned x = 0; x < LEVEL_WIDTH_; ++x) {
	//		int tile_type = grid_map_[x][y].type_;
	//		if (tile_type == 0 || tile_type == 32 || tile_type == 33 || tile_type == 34 || tile_type == 35) {
	//			std::cout << "[" << x << ", " << y << "] " << grid_map_[x][y].type_ << " Neighbors: ";
	//			for (unsigned i = 0; i < grid_map_[x][y].neighbors_.size(); ++i) {
	//				std::cout << "[" << grid_map_[x][y].neighbors_.at(i).x_ << " " << grid_map_[x][y].neighbors_.at(i).y_ << "] ";
	//			}
	//			std::cout << "\n";
	//		}
	//		else {
	//			//std::cout << grid_map_[x][y].type_ << "\n";
	//		}
	//		
	//	}	
	//}
}
