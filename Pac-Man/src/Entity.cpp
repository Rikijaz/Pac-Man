// Entity.cpp : Defines the Entity class's functions

#include "Entity.h"

#include <iostream>

int Entity::GetPosX() {
	return pos_x_;
}

int Entity::GetPosY() {
	return pos_y_;
}

SDL_Rect Entity::GetCBox() {
	return cbox_;
}

bool Entity::CheckCollision(SDL_Rect cbox) {
	return SDL_HasIntersection(&cbox_, &cbox);
}
