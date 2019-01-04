// Font.h : Defines the Font class's functions

#include "Font.h"

Font::Font(Data & data) {
	if (LoadFonts(data)) {
		std::cout << "Font has successfully initialized!\n";
	}
	else {
		std::cout << "Font failed to initialize!\n";
	}
}

Texture* Font::GetLetter(char letter) {
	return letters_.at(int(letter) - 65);
}

Texture* Font::GetNumber(int num) {
	return numbers_.at(num);
}

bool Font::LoadFonts(Data & data) {
	bool loaded_fonts = true;
	std::vector<Texture*> fonts;
	if (data.GetSprites("Fonts", fonts)) {
		for (unsigned i = 0; i < 26 && loaded_fonts; ++i) {
			if (i < fonts.size()) {
				letters_.push_back(fonts.at(i));
			}
			else {
				loaded_fonts = false;
			}		
		}
		for (unsigned i = 30; i < 40 && loaded_fonts; ++i) {
			if (i < fonts.size()) {
				numbers_.push_back(fonts.at(i));
			}
			else {
				loaded_fonts = false;
			}
		}
	}
	else {
		loaded_fonts = false;
	}

	return loaded_fonts;
}
