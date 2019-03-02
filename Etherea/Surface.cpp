#include "Surface.hpp"

Surface::Surface(SDL_Surface* surface) : surface(surface) {}

Surface::~Surface()
{
	if (surface)
		SDL_FreeSurface(surface);
}

Surface::Surface(Surface const& other) : surface(other.surface) {}

Surface Surface::FromBMP(string const& path)
{
	return Surface(SDL_LoadBMP(path.c_str()));
}
