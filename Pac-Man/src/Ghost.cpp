// Ghost.cpp : Defines the Ghost class's functions

#include "Ghost.h"

#include <random>

struct LessThanByDistance {
	bool operator()(const GridTile& lhs, const GridTile& rhs) const {
		return lhs.distance_ < rhs.distance_;
	}
};

Ghost::Ghost(int vel) : Character(vel) {}

void Ghost::CalculatePath(Level &level) {
	
}

bool Ghost::PlayerIsInScope() {
	bool is_in_scope = false;

	int x_diff = player_pos_.x_ - pos_.x_;
	int y_diff = player_pos_.y_ - pos_.y_;
	int distance = std::sqrt(x_diff * x_diff + y_diff * y_diff);

	if (distance <= GHOST_RANGE_) {
		is_in_scope = true;
		std::cout << distance << "\n";
	}

	return is_in_scope;
}

void Ghost::Wander(Level &level) {
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> r_direction(1, 4);
	std::uniform_int_distribution<std::mt19937::result_type> r_distance(96, 256);

	if (!is_moving_ || wander_distance_ <= 0) {
		input_direction_ += r_direction(rng);
		if (input_direction_ >= 4) {
			input_direction_ -= 4;
		}
		wander_distance_ = r_distance(rng);
		wander_start_pos_ = pos_;
	}
}

void Ghost::Drift(Level & level) {
	bool found_direction = false;

	bool unable_to_move_right = false;
	bool unable_to_move_left = false;
	bool unable_to_move_down = false;
	bool unable_to_move_up = false;

	// Player is to the right of the ghost
	if (player_pos_.x_ > pos_.x_ && (!found_direction)) {
		if (CanMoveRight(level)) {
			input_direction_ = MOVING_RIGHT;
			found_direction = true;
		}
		else {
			unable_to_move_right = true;
		}
	}

	// Player is to the left of the ghost
	if (player_pos_.x_ < pos_.x_ && (!found_direction)) {
		if (CanMoveLeft(level)) {
			input_direction_ = MOVING_LEFT;
			found_direction = true;
		}
		else {
			unable_to_move_left = true;
		}
	}

	// Player is to the south of the ghost
	if (player_pos_.y_ > pos_.y_ && (!found_direction)) {
		if (CanMoveDown(level)) {
			input_direction_ = MOVING_DOWN;
			found_direction = true;
		}
		else {
			unable_to_move_down = true;
		}
	}

	// Player is to the north of the ghost
	if (player_pos_.y_ < pos_.y_ && (!found_direction)) {
		if (CanMoveUp(level)) {
			input_direction_ = MOVING_UP;
			found_direction = true;
		}
		else {
			unable_to_move_up = true;
		}
	}

	// Player is stuck
	if (!found_direction) {
		if (unable_to_move_right && unable_to_move_up) {

		}
	}
}

void Ghost::DistanceWandered() {
	int x_diff = p_pos_.x_ - pos_.x_;
	int y_diff = p_pos_.y_ - pos_.y_;
	int distance = std::sqrt(x_diff * x_diff + y_diff * y_diff);

	wander_distance_ -= distance;
}

void Ghost::GetPlayerPos(Level &level) {
	player_pos_.x_ = level.GetCharacterGridTileX(PAC_MAN_CHAR_KEY);
	player_pos_.y_ = level.GetCharacterGridTileY(PAC_MAN_CHAR_KEY);
}
