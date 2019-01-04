// Player.cpp : Defines the Player class's functions

#include "Blinky.h"

Blinky::Blinky(Data & data, int pos_x, int pos_y) {
	// Get player spritesheet
	if (!data.GetSprites("Blinky", sprite_sheet_)) {
		std::cout << "Failed to retrieve textures from my_data_!\n";
	}
	else {
		// Initialize the collision box dimensions
		cbox_.w = sprite_sheet_.at(0)->GetWidth();
		cbox_.h = sprite_sheet_.at(0)->GetHeight();
		cbox_.x = pos_x_;
		cbox_.y = pos_y_;

		// Initialize the offsets
		pos_x_ = pos_x;
		pos_y_ = pos_y;

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

		std::cout << "Player has loaded successfully!\n";
	}
}

Blinky::~Blinky() {
}

void Blinky::Update(Level & level, int elapsed_time) {
}

void Blinky::Render(Graphics & graphics) {
}