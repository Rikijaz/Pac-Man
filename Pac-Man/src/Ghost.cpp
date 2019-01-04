// Ghost.cpp : Defines the Ghost class's functions

#include "Ghost.h"

Ghost::Ghost(int vel) : Character(vel) {}

void Ghost::GetPlayerPos(Level &level) {
	player_pos_x_ = level.GetCharacterTilePosX(PAC_MAN_CHAR_KEY);
	player_pos_y_ = level.GetCharacterTilePosY(PAC_MAN_CHAR_KEY);
}
