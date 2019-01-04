// Text.h : Declares the Text class's functions

#ifndef TEXT_H
#define TEXT_H

#include "Texture.h"
#include "Graphics.h"

class Text {
public:
	Text() {};

	Text(Texture* texture, int pos_x, int pos_y, char character);

	// Shows the tile
	void Render(Graphics &graphics);

	// Returns char_
	char GetChar();

private:
	// The X and Y offsets of the text
	int pos_x_;
	int pos_y_;

	Texture* texture_;
	char char_;
};

#endif // !TEXT_H
