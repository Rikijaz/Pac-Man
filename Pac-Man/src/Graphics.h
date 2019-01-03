// Graphics.h : Declares the Graphics class's functions

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Texture.h"

#include "SDL.h"
#include <string>


class Graphics {
	public:
		// Initializes variables
		Graphics();

		// Deallocates memory
		~Graphics();

		Texture* LoadFromFile(std::string path);

		// Clear screen
		void Clear();

		// Renders texture at given point
		void Render(int x, int y, Texture* texture, SDL_Rect* clip = NULL);

		// Update screen
		void Update();

	private:
		// Initializes SDL
		bool Initialize();

		// The window we'll be rendering to
		SDL_Window* window_ = NULL;

		// The window renderer
		SDL_Renderer* renderer_ = NULL;
};

#endif // !GRAPHICS_H
