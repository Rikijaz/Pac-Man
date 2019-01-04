// Entity.cpp : Defines the Entity class's functions

#include "Entity.h"

#include <iostream>

Pos Entity::GetPos() {
	return pos_;
}

SDL_Rect Entity::GetCBox() {
	return cbox_;
}

bool Entity::CheckCollision(SDL_Rect cbox) {
	return SDL_HasIntersection(&cbox_, &cbox);
}
