// Player.cpp : Defines the Player class's functions

#include "Player.h"

#include <iostream>
#include <cmath>

enum {
	MOVING_RIGHT,
	MOVING_DOWN,
	MOVING_LEFT,
	MOVING_UP,
};

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
	ExecuteInput(input);
	Move(level);
	EatDot(level);
	SetAnimation(elapsed_time);
}

void Player::Render(Graphics & graphics) {
	// Show the player
	graphics.Render(pos_, sprite_sheet_.at(frame_ + frame_offset_));
}

int Player::GetPacDotsEaten() {
	return pac_dots_eaten_;
}

int Player::GetPacPelletsEaten() {
	return pac_pellets_eaten_;
}

void Player::ExecuteInput(Input &input_) {
	if (input_.WasKeyHeld(SDL_SCANCODE_RIGHT)) {
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
		std::cout << "Player pos: " << pos_.x_ << ", " << pos_.y_ << "\n";
		//std::cout << "Points: " << pac_dots_eaten_ << " " << pac_pellets_eaten_ << "\n";
	}
}

void Player::Move(Level &level) {
	p_pos_.x_ = pos_.x_;
	p_pos_.y_ = pos_.y_;

	// If appropriate, teleport the player
	if (!TeleportPlayer(level)) {
		switch (input_direction_) {
			case MOVING_RIGHT: {
				if (CanMoveRight(level)) {
					curr_direction_ = input_direction_;
				}
				break;
			}
			case MOVING_DOWN: {
				if (CanMoveDown(level)) {
					curr_direction_ = input_direction_;
				}
				break;
			}
			case MOVING_LEFT: {
				if (CanMoveLeft(level)) {
					curr_direction_ = input_direction_;
				}
				break;
			}
			case MOVING_UP: {
				if (CanMoveUp(level)) {
					curr_direction_ = input_direction_;
				}
				break;
			}
			default: {
				curr_direction_ = input_direction_;
				break;
			}
		}
	}

	switch (curr_direction_) {
		case MOVING_RIGHT: {
			is_facing_right_ = true;
			is_facing_down_ = false;
			is_facing_left_ = false;
			is_facing_up_ = false;
			MoveRight(level);
			break;
		}
		case MOVING_DOWN: {
			is_facing_right_ = false;
			is_facing_down_ = true;
			is_facing_left_ = false;
			is_facing_up_ = false;
			MoveDown(level);
			break;
		}
		case MOVING_LEFT: {
			is_facing_right_ = false;
			is_facing_down_ = false;
			is_facing_left_ = true;
			is_facing_up_ = false;
			MoveLeft(level);
			break;
		}
		case MOVING_UP: {
			is_facing_right_ = false;
			is_facing_down_ = false;
			is_facing_left_ = false;
			is_facing_up_ = true;
			MoveUp(level);
			break;
		}
		default: {
			break;
		}
	}

	if (p_pos_.x_ == pos_.x_ && p_pos_.y_ == pos_.y_) {
		is_moving_ = false;
	}
	else {
		is_moving_ = true;
		level.SetCharacterGridTile(PAC_MAN_CHAR_KEY, pos_.x_, pos_.y_);
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

bool Player::TeleportPlayer(Level & level) {
	static const int LEFT_TELE_ENTRY = 0;
	static const int LEFT_TELE_EXIT = 2;
	static const int RIGHT_TELE_ENTRY = 3;
	static const int RIGHT_TELE_EXIT = 1;
	bool teleported = false;

	if (CheckCollision(level.GetTeleportTiles().at(LEFT_TELE_ENTRY)->GetCBox())) {
		pos_ = level.GetTeleportTiles().at(LEFT_TELE_EXIT)->GetPos();
		curr_direction_ = MOVING_LEFT;
		teleported = true;
	}
	if (CheckCollision(level.GetTeleportTiles().at(RIGHT_TELE_ENTRY)->GetCBox())) {
		pos_ = level.GetTeleportTiles().at(RIGHT_TELE_EXIT)->GetPos();
		curr_direction_ = MOVING_RIGHT;
		teleported = true;
	}

	return teleported;
}

bool Player::CanMoveRight(Level & level) {
	// Success flag
	bool can_move_right = true;

	pos_.x_ += VEL_;
	UpdateCBox();
	SDL_Rect collided_tile_cbox;
	if (GetCollidedTileCBox(level.GetCollisionTiles(), collided_tile_cbox)) {
		can_move_right = false;
	}

	pos_.x_ -= VEL_;
	UpdateCBox();

	return can_move_right;
}

bool Player::CanMoveDown(Level & level) {
	// Success flag
	bool can_move_down = true;

	pos_.y_ += VEL_;
	UpdateCBox();
	SDL_Rect collided_tile_cbox;
	if (GetCollidedTileCBox(level.GetCollisionTiles(), collided_tile_cbox)) {
		can_move_down = false;
	}

	pos_.y_ -= VEL_;
	UpdateCBox();

	return can_move_down;
}

bool Player::CanMoveLeft(Level & level) {
	// Success flag
	bool can_move_left = true;

	pos_.x_ -= VEL_;
	UpdateCBox();
	SDL_Rect collided_tile_cbox;
	if (GetCollidedTileCBox(level.GetCollisionTiles(), collided_tile_cbox)) {
		can_move_left = false;
	}

	pos_.x_ += VEL_;
	UpdateCBox();

	return can_move_left;
}

bool Player::CanMoveUp(Level & level) {
	// Success flag
	bool can_move_up = true;

	pos_.y_ -= VEL_;
	UpdateCBox();
	SDL_Rect collided_tile_cbox;
	if (GetCollidedTileCBox(level.GetCollisionTiles(), collided_tile_cbox)) {
		can_move_up = false;
	}

	pos_.y_ += VEL_;
	UpdateCBox();

	return can_move_up;
}