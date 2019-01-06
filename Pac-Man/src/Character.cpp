// Character.cpp : Defines the Character class's functions

#include "Character.h"

Character::Character(int vel) : VEL_(vel) {}

void Character::Move(Level &level) {
	p_pos_.x_ = pos_.x_;
	p_pos_.y_ = pos_.y_;



	// If appropriate, teleport the player
	if (!TeleportCharacter(level)) {
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
		UpdateMapPos(level);
	}
}

void Character::Render(Graphics & graphics) {
	// Show the player
	graphics.Render(pos_, sprite_sheet_.at(frame_ + frame_offset_));
}

void Character::MoveRight(Level &level) {
	pos_.x_ += VEL_;
	UpdateCBox();
	SDL_Rect collided_tile_cbox;
	if (GetCollidedTileCBox(level.GetCollisionTiles(), collided_tile_cbox)) {
		int intersect_dis = abs(cbox_.w - abs(collided_tile_cbox.x - cbox_.x));
		pos_.x_ -= intersect_dis;
		UpdateCBox();
	}

	double tile_pos_x = static_cast<double>(pos_.x_) / GLOBALS::TILE_WIDTH;
	tile_pos_.x_ = static_cast<int>(std::ceil(tile_pos_x));
}

void Character::MoveDown(Level &level) {
	pos_.y_ += VEL_;
	UpdateCBox();
	SDL_Rect collided_tile_cbox;
	if (GetCollidedTileCBox(level.GetCollisionTiles(), collided_tile_cbox)) {
		int intersect_dis = abs(cbox_.h - abs(collided_tile_cbox.y - cbox_.y));
		pos_.y_ -= intersect_dis;
		UpdateCBox();
	}

	double tile_pos_y = static_cast<double>(pos_.y_) / GLOBALS::TILE_HEIGHT;
	tile_pos_.y_ = static_cast<int>(std::ceil(tile_pos_y));
}

void Character::MoveLeft(Level &level) {
	pos_.x_ -= VEL_;
	UpdateCBox();
	SDL_Rect collided_tile_cbox;
	if (GetCollidedTileCBox(level.GetCollisionTiles(), collided_tile_cbox)) {
		int intersect_dis = abs(cbox_.w - abs(collided_tile_cbox.x - cbox_.x));
		pos_.x_ += intersect_dis;
		UpdateCBox();
	}

	double tile_pos_x = static_cast<double>(pos_.x_) / GLOBALS::TILE_WIDTH;
	tile_pos_.x_ = static_cast<int>(std::ceil(tile_pos_x));
}

void Character::MoveUp(Level &level) {
	pos_.y_ -= VEL_;
	UpdateCBox();
	SDL_Rect collided_tile_cbox;
	if (GetCollidedTileCBox(level.GetCollisionTiles(), collided_tile_cbox)) {
		int intersect_dis = abs(cbox_.h - abs(collided_tile_cbox.y - cbox_.y));
		pos_.y_ += intersect_dis;
		UpdateCBox();
	}

	double tile_pos_y = static_cast<double>(pos_.y_) / GLOBALS::TILE_HEIGHT;
	tile_pos_.y_ = static_cast<int>(std::ceil(tile_pos_y));
}

bool Character::CanMoveRight(Level & level) {
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

bool Character::CanMoveDown(Level & level) {
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

bool Character::CanMoveLeft(Level & level) {
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

bool Character::CanMoveUp(Level & level) {
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

bool Character::GetCollidedTileCBox(std::vector<Tile*> collision_tiles, SDL_Rect & cbox) {
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

void Character::SetAnimation(int elapsed_time) {
	if (is_facing_right_) {
		frame_offset_ = 0;
	}
	if (is_facing_down_) {
		frame_offset_ = 2;
	}
	if (is_facing_left_) {
		frame_offset_ = 4;
	}
	if (is_facing_up_) {
		frame_offset_ = 6;
	}

	// Regulate animation frame rate
	time_elapsed_ += elapsed_time;
	if (time_elapsed_ > time_to_update_) {
		time_elapsed_ -= time_to_update_;
		// If the player is not moving or end of animation sequence
		if (!is_moving_ || frame_ >= ANIMATION_FRAMES_ - 1) {
			frame_ = 0;
		}
		else {
			frame_++;
		}
	}
}

void Character::UpdateCBox() {
	cbox_.x = pos_.x_;
	cbox_.y = pos_.y_;
}

bool Character::TeleportCharacter(Level & level) {
	static const int LEFT_TELE_EXIT = 4;
	static const int RIGHT_TELE_EXIT = 3;
	bool teleported = false;

	if (LeftTeleTileCollision(level)) {
		pos_ = level.GetTeleportTiles().at(LEFT_TELE_EXIT)->GetPos();
		curr_direction_ = MOVING_LEFT;
		teleported = true;
	}
	if (RightTeleTileCollision(level)) {
		pos_ = level.GetTeleportTiles().at(RIGHT_TELE_EXIT)->GetPos();
		curr_direction_ = MOVING_RIGHT;
		teleported = true;
	}

	return teleported;
}

bool Character::LeftTeleTileCollision(Level & level) {
	bool tele_collision = false;
	for (unsigned i = 0; i < 3 && !tele_collision; ++i) {
		if (CheckCollision(level.GetTeleportTiles().at(i)->GetCBox())) {
			tele_collision = true;
		}
	}

	return tele_collision;
}

bool Character::RightTeleTileCollision(Level & level) {
	bool tele_collision = false;
	for (unsigned i = 5; i < 8 && !tele_collision; ++i) {
		if (CheckCollision(level.GetTeleportTiles().at(i)->GetCBox())) {
			tele_collision = true;
		}
	}

	return tele_collision;
}
