// Ghost.h : Declares the Ghost class's functions

#ifndef GHOST_H
#define GHOST_H

#include <SDL.h>

#include "Character.h"
#include "Graphics.h"
#include "Data.h"
#include "Input.h"
#include "Level.h"

class Ghost : public Character {
protected:
	// Updates the ghost
	virtual void Update(Level &level, int elapsed_time) = 0;

	// Calculate the path to the player


	// The X and Y offsets of the player
	int player_pos_x_;
	int player_pos_y_;

	// Ghost velocity
	static const int GHOST_VEL_ = 2;
};

#endif // !GHOST_H