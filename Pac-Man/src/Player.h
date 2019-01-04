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

	// Shows the player on the screen
	virtual void Render(Graphics &graphics);

	// Returns pac_dots_eaten_
	int GetPacDotsEaten();

	// Returns pac_pellets_eaten_
	int GetPacPelletsEaten();

private:
	// Execute input
	void ExecuteInput(Input &input_);

	// If the player can move towards the desired direction, move the player
	virtual void Move(Level &level);

	// If the player collides with a dot, eat it
	void EatDot(Level &level);

	// If the player collides with a teleport tile, teleport the player
	bool TeleportPlayer(Level &level);

	// Check if the player can move this direction
	bool CanMoveRight(Level &level);
	bool CanMoveDown(Level &level);
	bool CanMoveLeft(Level &level);
	bool CanMoveUp(Level &level);

	// Handles user input
	Input input_;

	// Player velocity
	static const int PLAYER_VEL_ = 4;

	// The input direction
	int input_direction_;

	// The direction the player is moving
	int curr_direction_;

	// The direction the player will move when possible
	int next_direction_;

	// Dots eaten counter
	int pac_dots_eaten_;
	int pac_pellets_eaten_;
};

#endif // !PLAYER_H