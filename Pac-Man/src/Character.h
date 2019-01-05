// Character.h : Declares the Character class's functions

#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL.h>
#include <vector>

#include "Entity.h"
#include "Texture.h"
#include "Graphics.h"
#include "Tile.h"
#include "Level.h"

enum {
	MOVING_RIGHT,
	MOVING_DOWN,
	MOVING_LEFT,
	MOVING_UP,
};

class Character : public Entity {
public:
	Character(int vel);

	// Shows the character on the screen
	virtual void Render(Graphics &graphics);

protected:
	// Moves the character
	void Move(Level &level);

	// Moves the character to the direction set
	void MoveRight(Level &level);
	void MoveDown(Level &level);
	void MoveLeft(Level &level);
	void MoveUp(Level &level);

	// Check if the character can move this direction
	bool CanMoveRight(Level &level);
	bool CanMoveDown(Level &level);
	bool CanMoveLeft(Level &level);
	bool CanMoveUp(Level &level);

	// If tile collision, get collided tile's collision box
	bool GetCollidedTileCBox(std::vector<Tile*> collision_tiles, SDL_Rect &cbox);

	// Cycle through the spritesheet appropriately
	void SetAnimation(int elapsed_time);

	// Update collision box
	void UpdateCBox();

	// Update position on grid_map_
	virtual void UpdateMapPos(Level &level) = 0;

	// If the player collides with a teleport tile, teleport the player
	bool TeleportCharacter(Level &level);

	// If the character is moving or not
	bool is_moving_;

	// Frame index offset
	int frame_offset_;

	// The previous X and Y offsets of the character
	Pos p_pos_;

	// The velocity of the character
	const int VEL_;
	int vel_x_;
	int vel_y_;

	// Check if the character is facing this direction
	bool is_facing_right_;
	bool is_facing_down_;
	bool is_facing_left_;
	bool is_facing_up_;

	// The input direction
	int input_direction_;

	// The direction the character is moving
	int curr_direction_;

	// The direction the character will move when possible
	int next_direction_;

	// Number of animation frames
	static const int ANIMATION_FRAMES_ = 2;

	static const int PAC_MAN_CHAR_KEY = 0;
	static const int BLINKY_CHAR_KEY = 1;
	static const int PINKY_CHAR_KEY = 2;
	static const int INKY_CHAR_KEY = 3;
	static const int CLYDE_CHAR_KEY = 4;

private:
	// Checks if the character has collided with a teleport tile
	bool LeftTeleTileCollision(Level &level);
	bool RightTeleTileCollision(Level &level);
};

#endif // !CHARACTER_H