#pragma once

#include "Common.hpp"
#include "Exception.hpp"
#include <SDL_surface.h>

class Surface {
	friend class Renderer;
public:
	Surface() = default;
	virtual ~Surface() = default;

	explicit Surface(SDL_Surface* surface);

	static Surface LoadIMG(string const& path);

	SDL_Color GetColorMod();
	void ColorMod(SDL_Color const& color);
	void ClearColorMod();
private:
	shared_ptr<SDL_Surface> ptr;
};

class SurfaceException : public SDLException {};
