// Data.cpp : Defines the Data class's functions

#include "Data.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

Data::Data(Graphics &graphics) {
	if (!LoadTextures(graphics)) {
		std::cout << "Failed to load textures.\n";
	}
}

Data::~Data() {
	for (unsigned i = 0; i < sprite_directory_.size(); ++i) {
		for (unsigned j = 0; j < sprite_directory_.at(i).sprite_list_.size(); ++j) {
			delete sprite_directory_.at(i).sprite_list_.at(j);
			sprite_directory_.at(i).sprite_list_.at(j) = NULL;
		}
	}
}

bool Data::GetSprites(std::string key, std::vector<Texture*> &sprite_list) {
	// Success flag
	bool valid_key = false;
	
	// Find the corresponding sprite sheet
	int sprite_sheet_index;
	for (unsigned i = 0; i < sprite_directory_.size(); ++i) {
		std::cout << sprite_directory_.at(i).key_ << "\n";
		if (sprite_directory_.at(i).key_ == key) {
			
			valid_key = true;
			sprite_sheet_index = i;
			break;
		}
	}

	// Load texture list
	if (valid_key) {
		sprite_list = sprite_directory_.at(sprite_sheet_index).sprite_list_;
	}
	else {
		std::cout << key << " does not exist in sprite_directory_.\n";
	}

	return valid_key;
}

bool Data::LoadTextures(Graphics &graphics) {
	// Success flag
	bool loaded_textures = true;

	// Open data.txt
	std::ifstream infs(DATA_FILE_PATH_);

	if (!infs.is_open()) {
		std::cout << DATA_FILE_PATH_ << " is an invalid file name!\n";
		loaded_textures = false;
	}
	// Parse data.txt for texture file names
	else {
		// Line reader
		std::string line;
		
		// Read in keys
		while (std::getline(infs, line) && loaded_textures) {
			if (line.at(0) == '*') {
				// Insert key into sprite_directory_
				std::string key = line.substr(1, line.size() - 1);
				
				std::getline(infs, line);
				// Get number of files for the key
				int total_files = std::stoi(line);

				// Load in textures from filenames here
				std::vector<Texture*> sprite_list;
				for (unsigned i = 0; i < total_files && loaded_textures; ++i) {
					// Read in file names
					std::getline(infs, line);				
					std::string path = SPRITE_FILE_PATH_ + line;
					Texture* new_texture = graphics.LoadFromFile(path);
					if (new_texture != NULL) {
						sprite_list.push_back(new_texture);
					}
					else {
						std::cout << line << " is an invalid file name!\n";
						loaded_textures = false;
					}
				}
				
				// If textures were successfully loaded, load key and mapped 
				// values into the sprite_directory_ 
				if (loaded_textures) {			
					Textures new_textures = { key, sprite_list };
					sprite_directory_.push_back(new_textures);
				}
			}
			else {
				std::cout << line << " is an invalid key!\n";
				loaded_textures = false;
			}
		}
		infs.close();
	}

	return loaded_textures;
}




