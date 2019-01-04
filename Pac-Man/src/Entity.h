// Entity.h : Declares the Entity class's functions

#ifndef ENTITY_H
#define ENTITY_H

#include "Graphics.h"
#include "Texture.h"

#include <SDL.h>
#include <vector>

class Entity {
public:
	// Shows entity on the screen
	virtual void Render(Graphics &graphics) = 0;

	// Returns pos_
	Pos GetPos();

	// Returns cbox_
	SDL_Rect GetCBox();

protected:
	// Box collision detector
	bool CheckCollision(SDL_Rect cbox);

	// The X and Y offsets of the entity
	Pos pos_;

	// The collision box 
	SDL_Rect cbox_;

	std::vector<Texture*> sprite_sheet_;

	// Time to update frame
	double time_to_update_;

	// Time elapsed since last frame update
	double time_elapsed_;

	// Current frame of animation
	int frame_;
};

#endif // !ENTITY_H
