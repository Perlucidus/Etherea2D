#include "Surface.hpp"

Surface::Surface(SDL_Surface* surface)
{
	ptr = shared_ptr<SDL_Surface>(surface, [=](SDL_Surface* p) { if (p) SDL_FreeSurface(p); STDLOG << "Surface Destroyed"; });
	setError(ptr.get());
}

Surface Surface::FromBMP(string const& path)
{
	return Surface(SDL_LoadBMP(path.c_str()));
}
