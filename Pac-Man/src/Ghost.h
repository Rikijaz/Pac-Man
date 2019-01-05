// Ghost.h : Declares the Ghost class's functions

#ifndef GHOST_H
#define GHOST_H

#include "Character.h"
#include "Graphics.h"
#include "Data.h"
#include "Input.h"
#include "Level.h"

#include <SDL.h>
#include <queue>

class Ghost : public Character {
public:
	Ghost(int vel);

protected:
	// Updates the ghost
	virtual void Update(Level &level, int elapsed_time) = 0;

	// Update position on grid_map_
	virtual void UpdateMapPos(Level &level) = 0;

	// Calculate the path to the player
	void CalculatePath(Level &level);

	// Check if the player is within the ghost's scope
	bool PlayerIsInScope();

	// Wanders around the map
	void Wander(Level &level);

	// Drift towards the player
	void Drift(Level &level);

	// Calculates the distance wandered
	void DistanceWandered();

	void GetPlayerPos(Level &level);

	// The X and Y offsets of the player
	Pos player_pos_;

	// Ghost velocity
	static const int GHOST_VEL_ = 2;

	// Ghost range
	static const int GHOST_RANGE_ = 5;

	// Position where the ghost starts to wander
	Pos wander_start_pos_;

	// The distance to wander
	int wander_distance_;

};

#endif // !GHOST_H