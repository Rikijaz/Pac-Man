// Game.cpp : Defines the Game class's functions

#include "Game.h"

#include <algorithm>
#include <iostream>
#include <vector>

const int FPS = 60;
const int MAX_FRAME_TIME = 1000 / FPS;
const int MS_PER_UPDATE = 16;

Game::Game() : 
		data_ (graphics_), 
		player_(data_, 416, 448),
		level_(data_),
		hud_(data_) {
	std::cout << "Game data loaded!\n";
	GameLoop();
}

Game::~Game() {}

void Game::GameLoop() {
	// Main loop flag
	bool quit = false;

	int last_update_time = SDL_GetTicks();
	int lag = 0;
	// While application is running
	while (!quit) {
		//std::cout << "New frame.\n";
		const int current_time = SDL_GetTicks();
		int elapsed_time = current_time - last_update_time;
		lag += elapsed_time;
		
		// Read and handle input
		quit = ProcessInput();

		//std::cout << lag << " : " << MS_PER_UPDATE << "\n";
		while (lag >= MS_PER_UPDATE) {
			// Update the game, one fixed step at a time, until it’s caught up.
			Update(std::min(elapsed_time, MAX_FRAME_TIME));
			
			lag -= MS_PER_UPDATE;
		}
		last_update_time = current_time;

		// Render to screen
		Render(lag / MS_PER_UPDATE);
	}
}

bool Game::ProcessInput() {
	bool user_wants_to_quit = false;

	input_.ResetKeyStates();
	if (SDL_PollEvent(&event_)) {
		if (event_.type == SDL_KEYDOWN && event_.key.repeat == 0) {
			input_.KeyDownEvent(event_);
		}
		else if (event_.type == SDL_KEYUP && event_.key.repeat == 0) {
			input_.KeyUpEvent(event_);
		}
		else if (event_.type == (SDL_QUIT)) {
			user_wants_to_quit = true;
		}
	}

	//player_.HandleInput(input_);

	return user_wants_to_quit;
}

void Game::Update(int elapsed_time) {
	player_.Update(input_, level_, elapsed_time);
}

void Game::Render(int elapsed_time) {
	//std::cout << "Rendering game.\n";
	// Clear screen
	graphics_.Clear();

	// Render screen
	level_.Render(graphics_);
	player_.Render(graphics_);
	hud_.Render(graphics_);
	


	//Update screen
	graphics_.Update();
}
