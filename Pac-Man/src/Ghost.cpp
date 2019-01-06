// Ghost.cpp : Defines the Ghost class's functions

#include "Ghost.h"

#include <random>
#include <deque>

Ghost::Ghost(int vel) : Character(vel) {}
    
bool Ghost::PlayerIsInScope() {
	bool is_in_scope = false;

	int x_diff = player_tile_pos_.x_ - tile_pos_.x_;
	int y_diff = player_tile_pos_.y_ - tile_pos_.y_;
	int distance = static_cast<int>(std::sqrt(x_diff * x_diff + y_diff * y_diff));

	if (distance <= GHOST_RANGE_) {
		is_in_scope = true;
	}

	return is_in_scope;
}

void Ghost::Wander(Level &level) {
	path_.clear();
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
	else {
		int x_diff = p_pos_.x_ - pos_.x_;
		int y_diff = p_pos_.y_ - pos_.y_;
		int distance = static_cast<int>(std::sqrt(x_diff * x_diff + y_diff * y_diff));

		wander_distance_ -= distance;
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

void Ghost::Pursue(Level & level) {
	if (path_.empty()) {
		std::map<Pos, Pos> bfs = GetBFSTraversal(level);
		path_ = ReconstructPathFromBFS(bfs);
	}
	else {
		FollowPath();
	}
}

void Ghost::GetPlayerPos(Level &level) {
	player_pos_ = level.GetCharacterPos(PAC_MAN_CHAR_KEY);
	player_tile_pos_ = level.GetCharacterTilePos(PAC_MAN_CHAR_KEY);
}

std::map<Pos, Pos> Ghost::GetBFSTraversal(Level & level) {
	Pos start_tile = tile_pos_;
	Pos end_tile = player_tile_pos_;
	std::queue<Pos> frontier;
	frontier.push(start_tile);

	std::map<Pos, Pos> bfs;
	bfs[start_tile] = start_tile;

	bool quit = false;
	while (!frontier.empty() && !quit) {
		Pos current = frontier.front();
		frontier.pop();

		if (current == end_tile) {
			break;
		}

		std::vector<Pos> neighbors = level.grid_map_[current.x_][current.y_].GetNeighbors();
		for (unsigned i = 0; i < neighbors.size(); ++i) {
			if (!bfs.count(neighbors.at(i))) {
				frontier.push(neighbors.at(i));
				bfs[neighbors.at(i)] = current;

				if (bfs[neighbors.at(i)] == end_tile) {
					quit = true;
				}
			}
		}
	}

	return bfs;
}

std::deque<Pos> Ghost::ReconstructPathFromBFS(std::map<Pos, Pos> BFS) {
	std::deque<Pos> path;
	Pos start_tile = tile_pos_;
	Pos end_tile = player_tile_pos_;

	Pos current = end_tile;
	bool start_found = false;
	while (!start_found) {
		if (current == start_tile) {
			start_found = true;
		}
		else {
			Pos came_from = BFS[current];
			path.push_front(current);
			current = came_from;
		}
	}

	return path;
}

void Ghost::FollowPath() {
	if (path_.front() == tile_pos_) {
		path_.pop_front();
	}
	
	if (!path_.empty()) {
		Pos next_tile = path_.front();

		// If the next step is east
		if (next_tile.x_ > tile_pos_.x_ && next_tile.y_ == tile_pos_.y_) {
			input_direction_ = MOVING_RIGHT;
		}
		// If the next step is west
		else if (next_tile.x_ < tile_pos_.x_ && next_tile.y_ == tile_pos_.y_) {
			input_direction_ = MOVING_LEFT;
		}
		// If the next step is south
		else if (next_tile.x_ == tile_pos_.x_ && next_tile.y_ > tile_pos_.y_) {
			input_direction_ = MOVING_DOWN;
		}
		// If the next step is north
		else if (next_tile.x_ == tile_pos_.x_ && next_tile.y_ < tile_pos_.y_) {
			input_direction_ = MOVING_UP;
		}
		else {
			std::cout << "Error: Ghost cannot calculate direction./n";
			std::cout << "Current ";
			tile_pos_.Output();
			std::cout << "Next ";
			next_tile.Output();
		}
	}
}