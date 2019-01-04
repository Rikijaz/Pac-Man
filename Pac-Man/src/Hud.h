// Hud.h : Declares the Hud class's functions

#ifndef HUD_H
#define HUD_H

#include "Graphics.h"
#include "Data.h"
#include "Font.h"
#include "Text.h"

class Hud {
public:
	Hud() {};

	// Deallocates memory
	~Hud();

	Hud(Data &data);

	// Shows the level
	void Render(Graphics &graphics);
private:
	// Creates the HUD
	bool InstantiateHud();

	Font font_;

	std::vector<Text*> high_score_text_;
	
	int HIGH_SCORES_TEXT_POS_X_ = 288;
	int HIGH_SCORES_TEXT_POS_Y_ = 0;

};

#endif // !HUD_H
