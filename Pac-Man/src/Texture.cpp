// Texture.cpp : Defines the Texture class's functions

#include "Texture.h"

#include <iostream>

Texture::Texture() {
	texture_ = NULL;
	width_ = 0;
	height_ = 0;
	angle_ = 0.0;
	center_ = NULL;
	flip_ = SDL_FLIP_NONE;
}

Texture::Texture(
		SDL_Texture * texture, 
		int width, 
		int height, 
		double angle, 
		SDL_Point * center, 
		SDL_RendererFlip flip) {
	texture_ = texture;
	width_ = width;
	height_ = height;
	angle_ = angle;
	center_ = center;
	flip_ = flip;
}

Texture::~Texture() {
	if (texture_ != NULL) {
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
		width_ = 0;
		height_ = 0;
		angle_ = 0.0;
		delete center_;
		center_ = NULL;
		flip_ = SDL_FLIP_NONE;
	}
	else {
		std::cout << "Unable to delete texture.\n";
	}
}

void Texture::SetAlpha(Uint8 alpha) {
	// Modulate texture alpha
	SDL_SetTextureAlphaMod(texture_, alpha);
}
void Texture::SetAngle(double angle) {
	angle_ = angle;
}

void Texture::SetCenter(int pos_x, int pos_y) {
	if (center_ != NULL) {
		delete center_;
	}
	center_ = new SDL_Point { pos_x, pos_y };
}

SDL_Texture * Texture::GetTexture() {
	return texture_;
}

int Texture::GetWidth() {
	return width_;
}

int Texture::GetHeight() {
	return height_;
}

double Texture::GetAngle() {
	return angle_;
}

SDL_Point* Texture::GetCenter() {
	return center_;
}

SDL_RendererFlip Texture::GetFlip() {
	return flip_;
}
