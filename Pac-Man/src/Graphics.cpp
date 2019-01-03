// Graphics.cpp : Defines the Graphics class's functions

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Globals.h"
#include "Graphics.h"

Graphics::Graphics() {
	if (Initialize()) {
		std::cout << "SDL has successfully initialized!\n";
	}
}

Graphics::~Graphics() {
	// Destroy window	
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	window_ = NULL;
	renderer_ = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

Texture* Graphics::LoadFromFile(std::string path) {
	// The final texture
	Texture* new_texture = NULL;

	// Load image at specified path
	SDL_Surface* loaded_surface = IMG_Load(path.c_str());
	if (loaded_surface == NULL) {
		std::cout << "Unable to load image from " << path << "!\n";
		std::cout << "SDL_image Error: " << IMG_GetError() << "\n";
	}
	else {
		// Color key image
		SDL_SetColorKey(
			loaded_surface,
			SDL_TRUE, 
			SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, loaded_surface);
		if (texture == NULL) {
			std::cout << "Unable to create texture from " << path << "!\n";
			std::cout << "SDL_image Error: " << IMG_GetError() << "\n";
		}
		else {
			// Get image dimensions
			new_texture = new Texture(
				texture, 
				loaded_surface->w, 
				loaded_surface->h);
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loaded_surface);
	}

	// Return finalized texture
	return new_texture;
}

void Graphics::Clear() {
	// white SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF); 
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0); 
	SDL_RenderClear(renderer_);
}

void Graphics::Render(int x, int y, Texture* texture, SDL_Rect * clip) {
	// Set rendering space and render to screen
	SDL_Rect render_rect = { x, y, texture->GetWidth(), texture->GetHeight() };

	// Set clip rendering dimensions
	if (clip != NULL) {
		render_rect.w = clip->w;
		render_rect.h = clip->h;
	}

	// Render to screen
	SDL_RenderCopyEx(
		renderer_, 
		texture->GetTexture(), 
		clip, 
		&render_rect, 
		texture->GetAngle(), 
		texture->GetCenter(), 
		texture->GetFlip());
}

void Graphics::Update() {
	SDL_RenderPresent(renderer_);
}

bool Graphics::Initialize() {
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failed to initialize SDL.\n";
		std::cout << "SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
	else {
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		// Create window
		window_ = SDL_CreateWindow(
			"Pac-Man", 
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			GLOBALS::SCREEN_WIDTH, 
			GLOBALS::SCREEN_HEIGHT, 
			SDL_WINDOW_SHOWN); // | SDL_WINDOW_INPUT_GRABBED  | SDL_WINDOW_RESIZABLE
		if (window_ == NULL) {
			std::cout << "Window could not be created!\n";
			std::cout << "SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}
		else {
			// Create vsynced renderer for window
			renderer_ = SDL_CreateRenderer(
				window_, 
				-1, 
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			/*renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);*/
			if (renderer_ == NULL) {
				std::cout << "Renderer could not be created!\n";
				std::cout << "SDL Error: " << SDL_GetError() << "\n";
				success = false;
			}
			else {
				// Initialize renderer color
				SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					std::cout << "SDL_image could not initialize!\n";
					std::cout << "SDL_image Error: " << IMG_GetError() << "\n";
					success = false;
				}
			}
		}
	}

	SDL_RenderSetScale(renderer_, GLOBALS::RES_SCALE_X, GLOBALS::RES_SCALE_Y);

	return success;
}
