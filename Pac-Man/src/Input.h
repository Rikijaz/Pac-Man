// Input.h : Declares the Input class's functions

#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <map>

class Input {
public:
	// Initialize variables
	Input();
	
	// Deallocate variables
	~Input();

	// Reset key states
	void ResetKeyStates();

	// When a key has been pressed
	void KeyDownEvent(const SDL_Event& event);

	// When a key is released
	void KeyUpEvent(const SDL_Event& event);

	// Read input and set keyboard/mouse states
	//void ProcessInput(SDL_Event &event);

	// Check if a key was pressed
	bool WasKeyPressed(SDL_Scancode key);

	// Check if a key was released
	bool WasKeyReleased(SDL_Scancode key);

	// Check if a key was held
	bool WasKeyHeld(SDL_Scancode key);

private:
	std::map<SDL_Scancode, bool> pressed_keys_;

	std::map<SDL_Scancode, bool> released_keys_;
	
	std::map<SDL_Scancode, bool> held_keys_;
};

#endif // !INPUT_H