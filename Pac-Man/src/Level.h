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

	// Returns tiles_
	std::vector<Tile*> GetTiles();

private:
	const std::string MAP_FILE_PATH_ = "data/map.txt";
	const std::string TILE_KEY = "Tiles";

	static const int TOTAL_TILES_ = 1008;
	static const int LEVEL_WIDTH_ = 28;
	static const int LEVEL_HEIGHT_ = 36;
	static const int TILE_WIDTH_ = 32;
	static const int TILE_HEIGHT_ = 32;

	// Read in the map and instantiate tiles
	bool ReadMapAndInstantiateTiles(Data &data);


	std::vector<Tile*> tiles_;

	std::vector<Texture*> sprite_list_;
};

#endif // !LEVEL_H
