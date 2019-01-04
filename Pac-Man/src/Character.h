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

class Character : public Entity {
public:
	Character(int vel);

protected:
	// Moves the character
	virtual void Move(Level &level) = 0;

	// Moves the character to the direction set
	void MoveRight(Level &level);
	void MoveDown(Level &level);
	void MoveLeft(Level &level);
	void MoveUp(Level &level);

	// If tile collision, get collided tile's collision box
	bool GetCollidedTileCBox(std::vector<Tile*> collision_tiles, SDL_Rect &cbox);

	// Cycle through the spritesheet appropriately
	void SetAnimation(int elapsed_time);

	// Update collision box
	void UpdateCBox();

	// If the character is moving or not
	bool is_moving_;

	// Frame index offset
	int frame_offset_;

	// The previous X and Y offsets of the entity
	int p_pos_x_;
	int p_pos_y_;

	// The velocity of the character
	const int VEL_;
	int vel_x_;
	int vel_y_;

	// Check if the player is facing this direction
	bool is_facing_right_;
	bool is_facing_down_;
	bool is_facing_left_;
	bool is_facing_up_;

	// Number of animation frames
	static const int ANIMATION_FRAMES_ = 2;

	static const int PAC_MAN_CHAR_KEY = 0;
	static const int BLINKY_MAN_CHAR_KEY = 1;
	static const int PINKY_MAN_CHAR_KEY = 2;
	static const int INKY_MAN_CHAR_KEY = 3;
	static const int CLYDE_MAN_CHAR_KEY = 4;
};

#endif // !CHARACTER_H