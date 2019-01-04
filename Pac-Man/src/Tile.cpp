// Tile.cpp : Defines the Tile class's functions

#include "Tile.h"

Tile::Tile(Texture* sprite, int pos_x, int pos_y, int tile_type) {
	// Initialize the offsets
	pos_.x_ = pos_x;
	pos_.y_ = pos_y;

	// Set the collision box
	cbox_.w = TILE_WIDTH_;
	cbox_.h = TILE_HEIGHT_;
	cbox_.x = pos_.x_;
	cbox_.y = pos_.y_;

	// Get the tile type
	type_ = tile_type;

	sprite_sheet_.push_back(sprite);
}

Tile::~Tile() {
}

void Tile::Render(Graphics & graphics) {
	// If the tile is on screen
	// Show the tile
	graphics.Render(pos_, sprite_sheet_.at(0));
}

int Tile::GetType() {
	return type_;
}
