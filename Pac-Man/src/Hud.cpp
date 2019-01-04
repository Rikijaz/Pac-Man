// Hud.h : Defines the Hud class's functions

#include "Hud.h"

Hud::~Hud() {
	for (unsigned i = 0; i < high_score_text_.size(); ++i) {
		delete high_score_text_.at(i);
		high_score_text_.at(i) = nullptr;
	}
	for (unsigned i = 0; i < MAX_SCORE_DIGITS_; ++i) {
		delete score_counter_text_[i];
		score_counter_text_[i] = nullptr;
	}
}

Hud::Hud(Data & data) : font_(data) {
	if (InstantiateHud()) {
		score_ = 0;
		score_digits_[0] = 0;
		score_digits_[1] = 0;
		score_digits_[2] = -1;
		score_digits_[3] = -1;
		score_digits_[4] = -1;
		score_digits_[5] = -1;
		pac_dots_last_eaten_ = 0;
		pac_pellets_last_eaten_ = 0;
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
	for (unsigned i = 0; i < MAX_SCORE_DIGITS_; ++i) {
		score_counter_text_[i]->Render(graphics);
	}
}

void Hud::Update(int pac_dots_eaten, int pac_pellets_eaten) {
	UpdateScoreValue(pac_dots_eaten, pac_pellets_eaten);
	UpdateScoreDisplay();
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

	// Draw score counter
	x = SCORE_ONES_POS_X_;
	y = SCORE_POS_Y_;
	score_counter_text_[0] = (new Text(font_.GetNumber(0), x, y, '0'));

	x = SCORE_TENS_POS_X_;
	score_counter_text_[1] = (new Text(font_.GetNumber(0), x, y, '0'));

	x = SCORE_HUNDREDS_POS_X_;
	score_counter_text_[2] = (new Text(font_.GetNumber(0), x, y, '0'));

	x = SCORE_THOUSANDS_POS_X_;
	score_counter_text_[3] = (new Text(font_.GetNumber(0), x, y, '0'));

	x = SCORE_T_THOUSANDS_POS_X_;
	score_counter_text_[4] = (new Text(font_.GetNumber(0), x, y, '0'));

	x = SCORE_H_THOUSANDS_POS_X_;
	score_counter_text_[5] = (new Text(font_.GetNumber(0), x, y, '0'));

	return true;
}

void Hud::UpdateScoreValue(int pac_dots_eaten, int pac_pellets_eaten) {
	// Update score_
	bool more_pac_dots_eaten = false;
	bool more_pac_pellets_eaten = false;

	if (pac_dots_eaten != pac_dots_last_eaten_) {
		more_pac_dots_eaten = true;
	}
	if (pac_pellets_eaten != pac_pellets_last_eaten_) {
		more_pac_pellets_eaten = true;
	}

	if (more_pac_dots_eaten) {
		score_ += 10 * (pac_dots_eaten - pac_dots_last_eaten_);
		pac_dots_last_eaten_ = pac_dots_eaten;
	}
	if (more_pac_pellets_eaten) {
		score_ += 50 * (pac_pellets_eaten - pac_pellets_last_eaten_);
		pac_pellets_last_eaten_ = pac_pellets_eaten;
	}

	// Update score_digits_
	score_digits_[0] = score_ % 10;
	score_digits_[1] = score_ % 100 / 10;
	score_digits_[2] = score_ % 1000 / 100;
	score_digits_[3] = score_ % 10000 / 1000;
	score_digits_[4] = score_ % 100000 / 10000;
	score_digits_[5] = score_ % 1000000 / 100000;
}

void Hud::UpdateScoreDisplay() {
	int x = SCORE_ONES_POS_X_;
	int y = SCORE_POS_Y_;
	Texture* updated_texture = font_.GetNumber(score_digits_[0]);
	char updated_char = '0' + score_digits_[0];
	score_counter_text_[0]->ChangeChar(updated_texture, updated_char);

	x = SCORE_TENS_POS_X_;
	updated_texture = font_.GetNumber(score_digits_[1]);
	updated_char = '0' + score_digits_[1];
	score_counter_text_[1]->ChangeChar(updated_texture, updated_char);

	x = SCORE_HUNDREDS_POS_X_;
	updated_texture = font_.GetNumber(score_digits_[2]);
	updated_char = '0' + score_digits_[2];
	score_counter_text_[2]->ChangeChar(updated_texture, updated_char);

	x = SCORE_THOUSANDS_POS_X_;
	updated_texture = font_.GetNumber(score_digits_[3]);
	updated_char = '0' + score_digits_[3];
	score_counter_text_[3]->ChangeChar(updated_texture, updated_char);

	x = SCORE_T_THOUSANDS_POS_X_;
	updated_texture = font_.GetNumber(score_digits_[4]);
	updated_char = '0' + score_digits_[4];
	score_counter_text_[4]->ChangeChar(updated_texture, updated_char);

	x = SCORE_H_THOUSANDS_POS_X_;
	updated_texture = font_.GetNumber(score_digits_[5]);
	updated_char = '0' + score_digits_[5];
	score_counter_text_[5]->ChangeChar(updated_texture, updated_char);
}

