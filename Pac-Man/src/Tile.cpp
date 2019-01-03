// Tile.cpp : Defines the Tile class's functions

#include "Tile.h"

Tile::Tile(Texture* sprite, int pos_x, int pos_y, int tile_type) {
	// Initialize the offsets
	pos_x_ = pos_x;
	pos_y_ = pos_y;

	// Set the collision box
	cbox_.w = TILE_WIDTH_;
	cbox_.h = TILE_HEIGHT_;
	cbox_.x = pos_x_;
	cbox_.y = pos_y_;

	// Get the tile type
	type_ = tile_type;

	sprite_sheet_.push_back(sprite);
}

Tile::~Tile() {
	for (unsigned i = 0; i < sprite_sheet_.size(); ++i) {
		delete sprite_sheet_.at(i);
	}
}

void Tile::Render(Graphics & graphics) {
	// If the tile is on screen
	// Show the tile
	graphics.Render(cbox_.x, cbox_.y, sprite_sheet_.at(0));
}

int Tile::GetType() {
	return type_;
}
