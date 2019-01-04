// Text.cpp : Defines the Text class's functions

#include "Text.h"

Text::Text(Texture* texture, int pos_x, int pos_y, char character) {
	// Initialize the offsets
	pos_x_ = pos_x;
	pos_y_ = pos_y;

	// Initialize character
	char_ = character;

	// Initialize font texture
	texture_ = texture;
}

void Text::Render(Graphics & graphics) {
	// Show the tile
	graphics.Render(pos_x_, pos_y_, texture_);
}

void Text::ChangeChar(Texture * texture, char character) {
	texture_ = texture;
	char_ = character;
}

char Text::GetChar() {
	return char_;
}
