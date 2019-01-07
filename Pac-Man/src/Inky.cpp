// Inky.cpp : Defines the Inky class's functions

#include "Inky.h"

Inky::Inky() : Ghost(INKY_VEL_) {}

Inky::Inky(Data & data, int pos_x, int pos_y) : Ghost(INKY_VEL_) {
	// Get player spritesheet
	if (!data.GetSprites("Inky", sprite_sheet_)) {
		std::cout << "Failed to retrieve textures from my_data_!\n";
	}
	else {
		// Initialize the offsets
		pos_.x_ = pos_x;
		pos_.y_ = pos_y;

		double tile_pos_x = static_cast<double>(pos_.x_) / GLOBALS::TILE_WIDTH;
		double tile_pos_y = static_cast<double>(pos_.y_) / GLOBALS::TILE_HEIGHT;
		tile_pos_.x_ = static_cast<int>(std::ceil(tile_pos_x));
		tile_pos_.y_ = static_cast<int>(std::ceil(tile_pos_y));

		// Initialize the collision box dimensions
		cbox_.w = sprite_sheet_.at(0)->GetWidth();
		cbox_.h = sprite_sheet_.at(0)->GetHeight();
		cbox_.x = pos_.x_;
		cbox_.y = pos_.y_;
		// Initialize the velocity
		vel_x_ = 0;
		vel_y_ = 0;

		// Initialize animation frame regulators
		frame_offset_ = 0;
		frame_ = 0;
		time_to_update_ = 100;
		time_elapsed_ = 0;
		is_moving_ = false;

		// Initialize direction

		is_facing_right_ = false;
		is_facing_down_ = false;
		is_facing_left_ = false;
		is_facing_up_ = false;

		std::cout << "Blinky has loaded successfully!\n";
	}
}

Inky::~Inky() {
}

void Inky::Update(Level & level, int elapsed_time) {
	std::cout << "Inky\n";
	GetPlayerPos(level);
	if (PlayerIsInScope()) {
		Pursue(level);
		//std::cout << "Inky is pursuing.\n";
	}
	else {
		Pursue(level);
		//std::cout << "Inky is wandering.\n";
	}
	Move(level);
	pos_.Output();
	tile_pos_.Output();
	SetAnimation(elapsed_time);
}

void Inky::UpdateMapPos(Level & level) {
	level.SetCharacterPos(INKY_CHAR_KEY, pos_);
	level.SetCharacterTilePos(INKY_CHAR_KEY, tile_pos_.x_, tile_pos_.y_);
}
