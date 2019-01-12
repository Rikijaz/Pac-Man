// Player.h : Declares the Player class's functions

#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

#include "Character.h"
#include "Graphics.h"
#include "Data.h"
#include "Input.h"
#include "Level.h"

class Player : public Character {
public:
	Player();

	// Initializes the variables
	Player(Data &data, int pos_x, int pos_y);

	// Deallocate memory
	~Player();

	// Updates the player
	void Update(Input &input, Level &level, int elapsed_time);

	// Returns pac_dots_eaten_
	int GetPacDotsEaten();

	// Returns pac_pellets_eaten_
	int GetPacPelletsEaten();

private:
	// Execute input
	void ExecuteInput(Input &input_);

	// If the player collides with a dot, eat it
	void EatDot(Level &level);

	// Update position on grid_map_
	virtual void UpdateMapPos(Level &level);

	// Handles user input
	Input input_;

	// Player velocity
	static const int PLAYER_VEL_ = 2;

	// Dots eaten counter
	int pac_dots_eaten_;
	int pac_pellets_eaten_;
};

#endif // !PLAYER_H