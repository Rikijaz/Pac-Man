// Input.h : Defines the Input class's functions

#include "Input.h"

#include <iostream>

Input::Input() {}

Input::~Input() {}

void Input::ResetKeyStates() {
	pressed_keys_.clear();
	released_keys_.clear();
}

void Input::KeyDownEvent(const SDL_Event& event) {
	pressed_keys_[event.key.keysym.scancode] = true;
	released_keys_[event.key.keysym.scancode] = false;
	held_keys_[event.key.keysym.scancode] = true;
}

void Input::KeyUpEvent(const SDL_Event& event) {
	pressed_keys_[event.key.keysym.scancode] = false;
	released_keys_[event.key.keysym.scancode] = true;
	held_keys_[event.key.keysym.scancode] = false;
}

bool Input::WasKeyPressed(SDL_Scancode key) {
	return pressed_keys_[key];
}

bool Input::WasKeyReleased(SDL_Scancode key) {
	return released_keys_[key];
}

bool Input::WasKeyHeld(SDL_Scancode key) {
	return held_keys_[key];
}
