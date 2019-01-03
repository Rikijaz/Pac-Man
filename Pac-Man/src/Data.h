// Data.h : Declares the Data class's functions

#ifndef DATA_H
#define DATA_H

#include "Texture.h"
#include "Graphics.h"

#include <SDL.h>
#include <string>
#include <map>
#include <vector>

struct Textures {
	std::string key_;
	std::vector<Texture*> sprite_list_;
};

class Data {
public:
	Data() {};

	// Load textures
	Data(Graphics &graphics);

	// Deallocate memory
	~Data();

	// Get appropriate textures
	bool GetSprites(std::string key, std::vector<Texture*> &sprite_list);

private:
	// Load all textures into texture_directory_
	bool LoadTextures(Graphics &graphics);
	
	// Contains all the sprites 
	std::vector<Textures> sprite_directory_;

	const std::string DATA_FILE_PATH_ = "data/assets_data.txt";

	const std::string SPRITE_FILE_PATH_ = "assets/sprites/";
};


#endif // !DATA_H

