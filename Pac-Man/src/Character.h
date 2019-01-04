// Character.h : Declares the Character class's functions

#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL.h>
#include <vector>

#include "Entity.h"
#include "Texture.h"
#include "Graphics.h"
#include "Tile.h"

class Character : public Entity {
public:

protected:
	// If the character is moving or not
	bool is_moving_;

	// The character's health pool
	int health_;

	// The previous X and Y offsets of the entity
	int p_pos_x_;
	int p_pos_y_;

	// The velocity of the character
	int vel_x_;

	int vel_y_;

	// The previous po
};

#endif // !CHARACTER_H
