// Inky.h : Declares the Inky class's functions

#ifndef INKY_H
#define INKY_H

#include <SDL.h>

#include "Ghost.h"
#include "Graphics.h"
#include "Data.h"
#include "Input.h"
#include "Level.h"

class Inky : public Ghost {
public:
	Inky();

	// Initializes the variables
	Inky(Data &data, int pos_x, int pos_y);

	// Deallocate memory
	~Inky();

	// Updates the player
	virtual void Update(Level &level, int elapsed_time);

	// Update position on grid_map_
	virtual void UpdateMapPos(Level &level);


private:
	static const int INKY_VEL_ = 2;
};

#endif // !INKY_H
