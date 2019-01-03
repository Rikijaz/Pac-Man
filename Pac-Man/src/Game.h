// Game.h : Declares the Game class's functions

#ifndef GAME_H
#define GAME_H

#include "Graphics.h"
#include "Player.h"
#include "Data.h"
#include "Input.h"
#include "Level.h"

#include <SDL.h>

class Game {
	public:
		// Initializes variables
		Game();

		// Deallocates memory
		~Game();

	private:
		// The main game loop
		void GameLoop();

		// Processes input and returns a command
		bool ProcessInput();

		// Updates the game
		void Update(float elapsed_time);

		// Draws window to screen
		void Render(float elapsed_time);

		// Event handler
		SDL_Event event_;

		// Creates and renders textures
		Graphics graphics_;

		// Contains all the sprites
		Data data_;

		// The player that the user will control
		Player player_;

		// The map the user will play in
		Level level_;

		// Handles user input
		Input input_;
};

#endif // !GAME_H
