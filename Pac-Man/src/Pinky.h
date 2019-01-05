// Pinky.h : Declares the Pinky class's functions

#ifndef PINKY_H
#define PINKY_H

#include <SDL.h>

#include "Ghost.h"
#include "Graphics.h"
#include "Data.h"
#include "Input.h"
#include "Level.h"

class Pinky : public Ghost {
public:
	Pinky();

	// Initializes the variables
	Pinky(Data &data, int pos_x, int pos_y);

	// Deallocate memory
	~Pinky();

	// Updates the player
	virtual void Update(Level &level, int elapsed_time);

	// Update position on grid_map_
	virtual void UpdateMapPos(Level &level);


private:
	static const int PINKY_VEL_ = 2;
};

#endif // !PINKY_H
