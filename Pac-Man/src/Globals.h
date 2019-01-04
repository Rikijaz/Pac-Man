// Globals.h : Defines the Global variables

namespace GLOBALS {
	const float RES_SCALE_X = 0.625;
	const float RES_SCALE_Y = 0.625;
	const int SCREEN_WIDTH = static_cast<int>(896 * RES_SCALE_X);
	const int SCREEN_HEIGHT = static_cast<int>(1152 * RES_SCALE_Y);
	const int LEVEL_WIDTH = 896;
	const int LEVEL_HEIGHT = 1152;
}

struct Pos {
	int x_;
	int y_;
};