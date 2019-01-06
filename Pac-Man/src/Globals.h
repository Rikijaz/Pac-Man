// Globals.h : Defines the Global variables

#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>

namespace GLOBALS {
	const float RES_SCALE_X = 0.625;
	const float RES_SCALE_Y = 0.625;
	const int SCREEN_WIDTH = static_cast<int>(896 * RES_SCALE_X);
	const int SCREEN_HEIGHT = static_cast<int>(1152 * RES_SCALE_Y);
	const int LEVEL_WIDTH = 896;
	const int LEVEL_HEIGHT = 1152;
	const int TILE_WIDTH = 32;
	const int TILE_HEIGHT = 32;
}

struct Pos {
	int x_;
	int y_;

	void Output() { std::cout << "Pos: [" << x_ << ", " << y_ << "]\n"; }

	bool operator==(const Pos &rhs) const { return (x_ == rhs.x_ && y_ == rhs.y_); };
	bool operator<(const Pos &rhs)  const { return x_ < rhs.x_ || x_ == rhs.x_ && y_ < rhs.y_; };
};

#endif // !GLOBALS_H