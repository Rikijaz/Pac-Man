// Blinky.h : Declares the Blinky class's functions

#ifndef BLINKY_H
#define BLINKY_H

#include <SDL.h>

#include "Ghost.h"
#include "Graphics.h"
#include "Data.h"
#include "Input.h"
#include "Level.h"

class Blinky : public Ghost {
public: 
	Blinky();

	// Initializes the variables
	Blinky(Data &data, int pos_x, int pos_y);

	// Deallocate memory
	~Blinky();

	// Updates the player
	virtual void Update(Level &level, int elapsed_time);

	// Update position on grid_map_
	virtual void UpdateMapPos(Level &level);


private:
	static const int BLINKY_VEL_ = 2;
};

#endif // !BLINKY_H
