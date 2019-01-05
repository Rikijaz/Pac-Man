// Clyde.h : Declares the Clyde class's functions

#ifndef CLYDE_H
#define CLYDE_H

#include <SDL.h>

#include "Ghost.h"
#include "Graphics.h"
#include "Data.h"
#include "Input.h"
#include "Level.h"

class Clyde : public Ghost {
public:
	Clyde();

	// Initializes the variables
	Clyde(Data &data, int pos_x, int pos_y);

	// Deallocate memory
	~Clyde();

	// Updates the player
	virtual void Update(Level &level, int elapsed_time);

	// Update position on grid_map_
	virtual void UpdateMapPos(Level &level);


private:
	static const int CLYDE_VEL_ = 2;
};

#endif // !CLYDE_H
