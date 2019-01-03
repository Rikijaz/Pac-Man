// Tile.h : Declares the Tile class's functions

#ifndef TILE_H
#define TILE_H

#include "Entity.h"

class Tile : public Entity {
public:
	// Tile dimensions
	static const int TILE_WIDTH_ = 32;
	static const int TILE_HEIGHT_ = 32;

	// Initializes position and type
	Tile(Texture* sprite, int pos_x, int pos_y, int tile_type);

	// Deallocates memory
	~Tile();

	// Shows the tile
	void Render(Graphics &graphics);

	// Returns tile type
	int GetType();

private:
	// The tile type
	int type_;
};

#endif // !TILE_H
