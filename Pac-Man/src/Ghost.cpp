// Ghost.cpp : Defines the Ghost class's functions

#include "Ghost.h"

Ghost::Ghost(int vel) : Character(vel) {}

void Ghost::CalculatePath(Level &level) {
	//std::queue<Pos> frontier;
	//Pos start = { pos_x_, pos_y_ };
	//Pos goal = { player_pos_x_, player_pos_y_ };
	//frontier.push(start);

	//std::map<int, std::map<int, Pos>> path_map;
	////path_map[start] = start;

	//while (!frontier.empty()) {
	//	Pos current = frontier.front();
	//	frontier.pop();

	//	if (current == goal) {
	//		break;
	//	}

	//	for (Location next : graph.neighbors(current)) {
	//		if (came_from.find(next) == came_from.end()) {
	//			frontier.push(next);
	//			came_from[next] = current;
	//		}
	//	}
	//}
	//return came_from;
}

void Ghost::GetPlayerPos(Level &level) {
	player_pos_.x_ = level.GetCharacterGridTileX(PAC_MAN_CHAR_KEY);
	player_pos_.y_ = level.GetCharacterGridTileY(PAC_MAN_CHAR_KEY);
}
