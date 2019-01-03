// Level.h : Declares the Level class's functions

#ifndef LEVEL_H
#define LEVEL_H

#include "Graphics.h"
#include "Data.h"
#include "Tile.h"


class Level {
public:
	Level() {};

	// Deallocates memory
	~Level();

	Level(Data &data);

	// Shows the level
	void Render(Graphics &graphics);

	// Returns collision_tiles_
	std::vector<Tile*> GetCollisionTiles();

	// Returns pac_dots_
	std::vector<Tile*> GetPacDots();

	// Returns pac_pellets_
	std::vector<Tile*> GetPacPellets();

	// Remove a Pac-Dot
	void RemovePacDot(int index);

	// Remove a Pac-Pellet
	void RemovePacPellet(int index);

private:
	const std::string MAP_FILE_PATH_ = "data/map.txt";
	const std::string TILE_KEY = "Tiles";

	static const int TOTAL_TILES_ = 1008;
	static const int LEVEL_WIDTH_ = 28;
	static const int LEVEL_HEIGHT_ = 36;
	static const int TILE_WIDTH_ = 32;
	static const int TILE_HEIGHT_ = 32;
	static const int TOTAL_COLLISION_TILES_ = 31;
	static const int TOTAL_PAC_DOTS_ = 33;
	static const int TOTAL_PAC_PELLETS_ = 32;

	// Read in the map and instantiate tiles
	bool ReadMapAndInstantiateTiles(Data &data);

	std::vector<Tile*> collision_tiles_;
	std::vector<Tile*> pac_dots_;
	std::vector<Tile*> pac_pellets_;

	std::vector<Texture*> sprite_list_;
};

#endif // !LEVEL_H
