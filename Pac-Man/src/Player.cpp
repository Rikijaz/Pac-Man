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

Player::Player(Data &data, int pos_x, int pos_y) {
	// Get player spritesheet
	if (!data.GetSprites("PacMan", sprite_sheet_)) {
		std::cout << "Failed to retrieve textures from my_data_!\n";
	}
	else {
		// Initialize the collision box dimensions
		cbox_.w = sprite_sheet_.at(0)->GetWidth();
		cbox_.h = sprite_sheet_.at(0)->GetHeight();
		cbox_.x = pos_x_;
		cbox_.y = pos_y_;

		std::cout << cbox_.w << cbox_.h;
		// Initialize the offsets
		pos_x_ = pos_x;
		pos_y_ = pos_y;

		// Initialize the velocity
		vel_x_ = 0;
		vel_y_ = 0;

		// Initialize animation frame regulators
		frame_ = 0;
		time_to_update_ = 0;
		time_elapsed_ = 0;
		is_moving_ = false;

		// Initialize direction
		input_direction_ = -1;
		curr_direction_ = -1;
		next_direction_ = -1;

		std::cout << "Successfully loaded Player data!\n";
	}
}

Player::~Player() {}


void Player::Update(Input &input, Level &level, int elapsed_time) {
	ExecuteInput(input);
	Move(level);
}

void Player::Render(Graphics & graphics) {
	// Show the player
	graphics.Render(pos_x_ , pos_y_, sprite_sheet_.at(frame_));
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
		std::cout << "Player pos: " << pos_x_ << ", " << pos_y_ << "\n";
	}
}

void Player::Move(Level &level) {
	std::cout << "Player pos: " << pos_x_ << ", " << pos_y_ << "\n";

	switch (input_direction_) {
		case MOVING_RIGHT: {
			if (CanMoveRight(level)) {
				std::cout << "Can't move right.\n";
				curr_direction_ = input_direction_;
			}
			else {
				std::cout << "Can move right.\n";
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

	switch (curr_direction_) {
		case MOVING_RIGHT: {
			MoveRight(level);
			break;
		}
		case MOVING_DOWN: {
			MoveDown(level);
			break;
		}
		case MOVING_LEFT: {
			MoveLeft(level);
			break;
		}
		case MOVING_UP: {
			MoveUp(level);
			break;
		}
		default: {
			std::cout << "Waiting for direction.\n";
			break;
		}
	}
}

void Player::MoveRight(Level &level) {
	pos_x_ += PLAYER_VEL_;
	UpdateCBox();
	SDL_Rect collided_tile_cbox;
	if (GetCollidedTileCBox(level.GetTiles(), collided_tile_cbox)) {
		int intersect_dis = abs(cbox_.w - abs(collided_tile_cbox.x - cbox_.x));
		pos_x_ -= intersect_dis;
		UpdateCBox();
	}
}

void Player::MoveDown(Level &level) {
	pos_y_ += PLAYER_VEL_;
	UpdateCBox();
	SDL_Rect collided_tile_cbox;
	if (GetCollidedTileCBox(level.GetTiles(), collided_tile_cbox)) {
		int intersect_dis = abs(cbox_.h - abs(collided_tile_cbox.y - cbox_.y));
		pos_y_ -= intersect_dis;
		UpdateCBox();
	}
}

void Player::MoveLeft(Level &level) {
	pos_x_ -= PLAYER_VEL_;
	UpdateCBox();
	SDL_Rect collided_tile_cbox;
	if (GetCollidedTileCBox(level.GetTiles(), collided_tile_cbox)) {
		int intersect_dis = abs(cbox_.w - abs(collided_tile_cbox.x - cbox_.x));
		pos_x_ += intersect_dis;
		UpdateCBox();
	}
}

void Player::MoveUp(Level &level) {
	pos_y_ -= PLAYER_VEL_;
	UpdateCBox();
	SDL_Rect collided_tile_cbox;
	if (GetCollidedTileCBox(level.GetTiles(), collided_tile_cbox)) {
		int intersect_dis = abs(cbox_.h - abs(collided_tile_cbox.y - cbox_.y));
		pos_y_ += intersect_dis;
		UpdateCBox();
	}
}

bool Player::CanMoveRight(Level & level) {
	// Success flag
	bool can_move_right = true;

	pos_x_ += PLAYER_VEL_;
	UpdateCBox();
	SDL_Rect collided_tile_cbox;
	if (GetCollidedTileCBox(level.GetTiles(), collided_tile_cbox)) {
		can_move_right = false;
	}

	pos_x_ -= PLAYER_VEL_;
	UpdateCBox();

	return can_move_right;
}

bool Player::CanMoveDown(Level & level) {
	// Success flag
	bool can_move_down = true;

	pos_y_ += PLAYER_VEL_;
	UpdateCBox();
	SDL_Rect collided_tile_cbox;
	if (GetCollidedTileCBox(level.GetTiles(), collided_tile_cbox)) {
		can_move_down = false;
	}

	pos_y_ -= PLAYER_VEL_;
	UpdateCBox();

	return can_move_down;
}

bool Player::CanMoveLeft(Level & level) {
	// Success flag
	bool can_move_left = true;

	pos_x_ -= PLAYER_VEL_;
	UpdateCBox();
	SDL_Rect collided_tile_cbox;
	if (GetCollidedTileCBox(level.GetTiles(), collided_tile_cbox)) {
		can_move_left = false;
	}

	pos_x_ += PLAYER_VEL_;
	UpdateCBox();

	return can_move_left;
}

bool Player::CanMoveUp(Level & level) {
	// Success flag
	bool can_move_up = true;

	pos_y_ -= PLAYER_VEL_;
	UpdateCBox();
	SDL_Rect collided_tile_cbox;
	if (GetCollidedTileCBox(level.GetTiles(), collided_tile_cbox)) {
		can_move_up = false;
	}

	pos_y_ += PLAYER_VEL_;
	UpdateCBox();

	return can_move_up;
}

bool Player::GetCollidedTileCBox(std::vector<Tile*> collision_tiles, SDL_Rect &cbox) {
	bool collided_tile = false;
	int collided_tile_pos = -1;
	for (unsigned i = 0; i < collision_tiles.size() && !collided_tile; ++i) {
		if (CheckCollision(collision_tiles.at(i)->GetCBox())) {
			collided_tile = true;
			collided_tile_pos = i;
		}
	}

	if (collided_tile) {
		cbox = collision_tiles.at(collided_tile_pos)->GetCBox();
	}

	return collided_tile;
}

void Player::UpdateCBox() {
	cbox_.x = pos_x_;
	cbox_.y = pos_y_;
}



