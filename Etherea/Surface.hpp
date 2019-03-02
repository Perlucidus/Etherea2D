#pragma once

#include "Common.hpp"
#include "SDLComponent.hpp"

class Surface : public SDLComponent {
	friend class Renderer;
public:
	Surface() = default;
	virtual ~Surface() = default;

	explicit Surface(SDL_Surface* surface);
public:
	static Surface FromBMP(string const& path);
private:
	class SurfaceDeleter;
private:
	shared_ptr<SDL_Surface> ptr;
};
