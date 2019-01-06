// GridTile.h : Declares the GridTile class's functions

#ifndef GRIDTILE_H
#define GRIDTILE_H

#include <vector>

#include "Globals.h"

class GridTile {
public:
	GridTile();

	GridTile(Pos pos, int type);

	bool operator==(const GridTile &rhs) const { return pos_ == rhs.pos_; }

	Pos GetPos();

	int GetType();

	void SetNeighbors(std::vector<Pos> neighbors);

	std::vector<Pos> GetNeighbors();

private:
	Pos pos_ = { -1, -1 };

	int type_ = -1;

	int distance_ = INT_MAX;

	bool visited_ = false;

	std::vector<Pos> neighbors_;
};

#endif // !GRIDTILE_H
