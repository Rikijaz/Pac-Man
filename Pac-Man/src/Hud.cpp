// Hud.h : Defines the Hud class's functions

#include "Hud.h"

Hud::~Hud() {
}

Hud::Hud(Data & data) : font_(data) {
	if (InstantiateHud()) {
		std::cout << "Hud has successfully loaded!\n";
	}
	else {
		std::cout << "Hud has failed to load!\n";
	}
}

void Hud::Render(Graphics & graphics) {
	for (unsigned i = 0; i < high_score_text_.size(); ++i) {
		high_score_text_.at(i)->Render(graphics);
	}
}

bool Hud::InstantiateHud() {
	// Draw "HIGH SCORE" text
	int x = HIGH_SCORES_TEXT_POS_X_;
	int y = HIGH_SCORES_TEXT_POS_Y_;

	high_score_text_.push_back(new Text(font_.GetLetter('H'), x, y, 'H'));
	x += 32;
	high_score_text_.push_back(new Text(font_.GetLetter('I'), x, y, 'I'));
	x += 32;
	high_score_text_.push_back(new Text(font_.GetLetter('G'), x, y, 'G'));
	x += 32;
	high_score_text_.push_back(new Text(font_.GetLetter('H'), x, y, 'H'));
	x += 32;
	x += 32;
	high_score_text_.push_back(new Text(font_.GetLetter('S'), x, y, 'S'));
	x += 32;
	high_score_text_.push_back(new Text(font_.GetLetter('C'), x, y, 'C'));
	x += 32;
	high_score_text_.push_back(new Text(font_.GetLetter('O'), x, y, 'O'));
	x += 32;
	high_score_text_.push_back(new Text(font_.GetLetter('R'), x, y, 'R'));
	x += 32;
	high_score_text_.push_back(new Text(font_.GetLetter('E'), x, y, 'E'));
	x += 32;

	return true;
}
