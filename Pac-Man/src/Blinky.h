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
	Blinky() {};

	// Initializes the variables
	Blinky(Data &data, int pos_x, int pos_y);

	// Deallocate memory
	~Blinky();

	// Updates the player
	virtual void Update(Level &level, int elapsed_time);

	// Shows the player on the screen
	virtual void Render(Graphics &graphics);
};
#endif // !BLINKY_H
