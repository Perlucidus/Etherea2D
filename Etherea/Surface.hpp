#pragma once

#include "Common.hpp"
#include "SDLComponent.hpp"

class Surface : public SDLComponent {
	friend class Renderer;
public:
	Surface() = delete;

	explicit Surface(SDL_Surface* surface);
	virtual ~Surface();
private:
	Surface(Surface const& other);
public:
	static Surface FromBMP(string const& path);
private:
	SDL_Surface* ptr;
};
