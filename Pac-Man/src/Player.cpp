// Player.cpp : Defines the Player class's functions

#include "Player.h"

#include <iostream>
#include <cmath>

Player::Player() : Character(PLAYER_VEL_) {
}

Player::Player(Data &data, int pos_x, int pos_y) : Character(PLAYER_VEL_) {
	// Get player spritesheet
	if (!data.GetSprites("PacMan", sprite_sheet_)) {
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
		input_direction_ = -1;
		curr_direction_ = -1;
		next_direction_ = -1;

		is_facing_right_ = false;
		is_facing_down_ = false;
		is_facing_left_ = false;
		is_facing_up_ = false;

		// Initialize counters
		pac_dots_eaten_ = 0;
		pac_pellets_eaten_ = 0;

		std::cout << "Player has loaded successfully!\n";
	}
}

Player::~Player() {}


void Player::Update(Input &input, Level &level, int elapsed_time) {
	UpdateMapPos(level);
	ExecuteInput(input);
	Move(level);
	EatDot(level);
	SetAnimation(elapsed_time);
}

int Player::GetPacDotsEaten() {
	return pac_dots_eaten_;
}

int Player::GetPacPelletsEaten() {
	return pac_pellets_eaten_;
}

void Player::ExecuteInput(Input &input_) {
	if (input_.WasKeyPressed(SDL_SCANCODE_RIGHT)) {
		input_direction_ = MOVING_RIGHT;
	}
	if (input_.WasKeyHeld(SDL_SCANCODE_DOWN)) {
		input_direction_ = MOVING_DOWN;
	}
	if (input_.WasKeyHeld(SDL_SCANCODE_LEFT)) {
		input_direction_ = MOVING_LEFT;
	}
	if (input_.WasKeyHeld(SDL_SCANCODE_UP)) {
		input_direction_ = MOVING_UP;
	}
	if (input_.WasKeyHeld(SDL_SCANCODE_SPACE)) {
		std::cout << "======================================================\n";
		std::cout << "Player pos: " << pos_.x_ << ", " << pos_.y_ << "\n";
		std::cout << "Tile pos: " << tile_pos_.x_ << ", " << tile_pos_.y_ << "\n";
		//std::cout << "Points: " << pac_dots_eaten_ << " " << pac_pellets_eaten_ << "\n";
		std::cout << "======================================================\n";
	}
}

void Player::EatDot(Level & level) {
	for (unsigned i = 0; i < level.GetPacDots().size(); ++i) {
		if (CheckCollision(level.GetPacDots().at(i)->GetCBox())) {
			level.RemovePacDot(i);
			pac_dots_eaten_++;
		}
	}
	for (unsigned i = 0; i < level.GetPacPellets().size(); ++i) {
		if (CheckCollision(level.GetPacPellets().at(i)->GetCBox())) {
			level.RemovePacPellet(i);
			pac_pellets_eaten_++;
		}
	}
}

void Player::UpdateMapPos(Level & level) {
	level.SetCharacterPos(PAC_MAN_CHAR_KEY, pos_);
	level.SetCharacterTilePos(PAC_MAN_CHAR_KEY, tile_pos_.x_, tile_pos_.y_);
}

