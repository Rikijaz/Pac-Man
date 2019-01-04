// Character.cpp : Defines the Character class's functions

#include "Character.h"

Character::Character(int vel) : VEL_(vel) {}

void Character::MoveRight(Level &level) {
	pos_x_ += VEL_;
	UpdateCBox();
	SDL_Rect collided_tile_cbox;
	if (GetCollidedTileCBox(level.GetCollisionTiles(), collided_tile_cbox)) {
		int intersect_dis = abs(cbox_.w - abs(collided_tile_cbox.x - cbox_.x));
		pos_x_ -= intersect_dis;
		UpdateCBox();
	}
}

void Character::MoveDown(Level &level) {
	pos_y_ += VEL_;
	UpdateCBox();
	SDL_Rect collided_tile_cbox;
	if (GetCollidedTileCBox(level.GetCollisionTiles(), collided_tile_cbox)) {
		int intersect_dis = abs(cbox_.h - abs(collided_tile_cbox.y - cbox_.y));
		pos_y_ -= intersect_dis;
		UpdateCBox();
	}
}

void Character::MoveLeft(Level &level) {
	pos_x_ -= VEL_;
	UpdateCBox();
	SDL_Rect collided_tile_cbox;
	if (GetCollidedTileCBox(level.GetCollisionTiles(), collided_tile_cbox)) {
		int intersect_dis = abs(cbox_.w - abs(collided_tile_cbox.x - cbox_.x));
		pos_x_ += intersect_dis;
		UpdateCBox();
	}
}

void Character::MoveUp(Level &level) {
	pos_y_ -= VEL_;
	UpdateCBox();
	SDL_Rect collided_tile_cbox;
	if (GetCollidedTileCBox(level.GetCollisionTiles(), collided_tile_cbox)) {
		int intersect_dis = abs(cbox_.h - abs(collided_tile_cbox.y - cbox_.y));
		pos_y_ += intersect_dis;
		UpdateCBox();
	}
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
	cbox_.x = pos_x_;
	cbox_.y = pos_y_;
}
