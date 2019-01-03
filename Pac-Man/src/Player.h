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
	Player() {};

	// Initializes the variables
	Player(Data &data, int pos_x, int pos_y);

	// Deallocate memory
	~Player();

	// Updates the player
	void Update(Input &input, Level &level, int elapsed_time);

	// Shows the player on the screen
	virtual void Render(Graphics &graphics);


private:
	// Execute input
	void ExecuteInput(Input &input_);

	// If tile collision, get collided tile's collision box
	bool GetCollidedTileCBox(std::vector<Tile*> collision_tiles, SDL_Rect &cbox);

	// Update collision box
	void UpdateCBox();

	// If the player can move towards the desired direction, move the player
	void Move(Level &level);

	// Cycle through the spritesheet appropriately
	void SetAnimation(int elapsed_time);

	// Moves the player to the direction set
	void MoveRight(Level &level);
	void MoveDown(Level &level);
	void MoveLeft(Level &level);
	void MoveUp(Level &level);

	// Check if the player can move this direction
	bool CanMoveRight(Level &level);
	bool CanMoveDown(Level &level);
	bool CanMoveLeft(Level &level);
	bool CanMoveUp(Level &level);

	// Handles user input
	Input input_;
	
	std::vector<Texture*> curr_animations;

	// Player velocity
	static const int PLAYER_VEL_ = 4;

	// Number of animation frames
	static const int ANIMATION_FRAMES_ = 2;

	// Frame index offset
	int frame_offset_;

	// The input direction
	int input_direction_;

	// The direction the player is moving
	int curr_direction_;

	// The direction the player will move when possible
	int next_direction_;

	// Check if the player is facing this direction
	bool is_facing_right_;
	bool is_facing_down_;
	bool is_facing_left_;
	bool is_facing_up_;
};

#endif // !PLAYER_H
