// Font.h : Declares the Font class's functions

#ifndef FONT_H
#define FONT_H

#include "Graphics.h"
#include "Data.h"

class Font {
public:
	Font() {};

	// Initialize variables
	Font(Data &data);

	// Deallocate memory
	~Font() {};

	// Get certain letter's texture
	Texture* GetLetter(char letter);

	// Get certain number's texture
	Texture* GetNumber(int num);
private:
	bool LoadFonts(Data &data);

	std::vector<Texture*> letters_;
	std::vector<Texture*> numbers_;
	
};

#endif // 
