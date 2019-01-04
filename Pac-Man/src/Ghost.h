// Ghost.h : Declares the Ghost class's functions

#ifndef GHOST_H
#define GHOST_H

#include "Character.h"
#include "Graphics.h"
#include "Data.h"
#include "Input.h"
#include "Level.h"

#include <SDL.h>
#include <queue>

class Ghost : public Character {
public:
	Ghost(int vel);

protected:
	// Updates the ghost
	virtual void Update(Level &level, int elapsed_time) = 0;

	// Calculate the path to the player
	void CalculatePath(Level &level);

	void GetPlayerPos(Level &level);

	// The X and Y offsets of the player
	Pos player_pos_;

	// Ghost velocity
	static const int GHOST_VEL_ = 2;
};

#endif // !GHOST_H