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

	// Update the hud's variables
	void Update(int pac_dots_eaten, int pac_pellets_eaten);

private:
	// Creates the HUD
	bool InstantiateHud();

	// Check if the player has eaten more dots since last update. If so,
	// appropriately increment score
	void UpdateScoreValue(int pac_dots_eaten, int pac_pellets_eaten);

	// Update text displayed
	void UpdateScoreDisplay();

	static const int MAX_SCORE_DIGITS_ = 6;

	static const int HIGH_SCORES_TEXT_POS_X_ = 288;
	static const int HIGH_SCORES_TEXT_POS_Y_ = 0;

	static const int SCORE_ONES_POS_X_ = 192;
	static const int SCORE_POS_Y_ = 32;
	static const int SCORE_TENS_POS_X_ = 160;
	static const int SCORE_HUNDREDS_POS_X_ = 128;
	static const int SCORE_THOUSANDS_POS_X_ = 96;
	static const int SCORE_T_THOUSANDS_POS_X_ = 64;
	static const int SCORE_H_THOUSANDS_POS_X_ = 32;

	// Score value
	int score_;

	// Score value tokenized by digits
	int score_digits_[MAX_SCORE_DIGITS_];

	int pac_dots_last_eaten_;
	int pac_pellets_last_eaten_;

	Font font_;

	std::vector<Text*> high_score_text_;
	Text* score_counter_text_[MAX_SCORE_DIGITS_];
	
	
	
};

#endif // !HUD_H
