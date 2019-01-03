// Texture.h : Declares the Texture class's functions

#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include "Debug.h"

#include <string>

class Texture {
	public:
		// Initializes variables to 0
		Texture();

		// Initializes variables
		Texture(
			SDL_Texture* texture, 
			int width, int height, 
			double angle = 0.0, 
			SDL_Point* center = NULL, 
			SDL_RendererFlip flip = 
			SDL_FLIP_NONE);

		// Deallocates memory
		~Texture();

		// Set alpha modulation
		void SetAlpha(Uint8 alpha);

		// Set angle
		void SetAngle(double angle);

		// Set center
		void SetCenter(int pos_x, int pos_y);

		// Returns texture_
		SDL_Texture* GetTexture();

		// Returns width_
		int GetWidth();

		// Returns height_
		int GetHeight();

		// Returns angle_
		double GetAngle();

		// Returns center_
		SDL_Point* GetCenter();

		// Returns flip_
		SDL_RendererFlip GetFlip();

	private:
		SDL_Texture* texture_;

		int width_;

		int height_;

		double angle_;

		SDL_Point* center_;

		SDL_RendererFlip flip_;

};

#endif // !TEXTURE_H